
#ifndef STONECOLD_ECS_ENTITYCOMPONENTSYSTEM_H
#define STONECOLD_ECS_ENTITYCOMPONENTSYSTEM_H

#include <array>
#include <queue>
#include "Types.hpp"
#include "System.hpp"
#include "ComponentMasks.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::ECS {

using namespace StoneCold::Common;

//
// Entity-Component-System (Manager)
// based on: https://austinmorlan.com/posts/entitycomponent_system/
//
// Managing the creation and destruction of Entities. This includes distributing
// Entity IDs and keeping record of which IDs are in use and which are not.
//
class EntityComponentSystem {
public:
	EntityComponentSystem(scUint32 maxEntities);

	EntityComponentSystem(const EntityComponentSystem&) = delete;
	EntityComponentSystem& operator=(const EntityComponentSystem&) = delete;

	// ------------------- ENTITYS -------------------

public:
	scEntityId CreateEntity() {
		if (_availableEntities.size() == 0)
			throw std::out_of_range("No more Entity Ids available");

		// Get the first available ID of the queue
		scEntityId id = _availableEntities.front();
		_availableEntities.pop();
		// Reset the new Entities ComponentMask
		_entityComponents[id] = 0;
		return id;
	}

	void DestroyEntity(scEntityId entityId) {
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : _componentWorld) {
			auto const& component = pair.second;
			component->DestroyEntity(entityId);
		}
		// Invalidate the destroyed entity's ComponentMask
		// Put the destroyed ID at the back of the queue
		_entityComponents[entityId] = 0;
		_availableEntities.push(entityId);
	}

	// ------------------- COMPONENTS -------------------

public:
	template<typename T>
	void AddComponent(scEntityId entityId, T&& component) {
		// In case the ECS World does not contain a ComponentArray of the specified Type, initialize it first
		scHash componentHash = GetTypeHash<T>();
		if(_componentWorld.find(componentHash) == _componentWorld.end())
			_componentWorld.insert({ componentHash, std::make_shared<EntityComponentArray<T>>(_maxEntities) });

		// Add the Entity (and the component values) to the specific Component Array
		GetComponentArray<T>()->insert(entityId, std::move(component));
		// Add the Component Flag to the mask (OR bitmask with the current value)
		_entityComponents[entityId] |= ComponentMasks[GetTypeHash<T>()];
		UpdateSystems(entityId, _entityComponents[entityId]);
	}

	template<typename T>
	void RemoveComponent(scEntityId entityId) {
		// Remove the Entitiy (and its component values) from a specific Component Array
		GetComponentArray<T>()->erase(entityId);
		// Remove the Component Flag from the mask (AND with the inverse of the bitmask)
		_entityComponents[entityId] &= ~ComponentMasks[GetTypeHash<T>()];
		UpdateSystems(entityId, _entityComponents[entityId]);
	}

	//
	// Get the statically casted pointer to the ComponentArray of type T
	//
	template<typename T>
	inline EntityComponentArray<T>* GetComponentArray() {
		return dynamic_cast<EntityComponentArray<T>*>(_componentWorld[GetTypeHash<T>()].get());
	}

	// ------------------- SYSTEMS -------------------

public:
	template<typename T>
	void AddSystem(std::shared_ptr<System> system) {
		_systems.insert({ GetTypeHash<T>(), system });
	}

	//
	// Workaround to set a additional Entity mask without a specific Component 
	// (adding a Component always means adding a full Array of n Components)
	//
	void AddAdditionalSystemMask(scEntityId entityId, scBitMask64 additionalMask) {
		_entityComponents[entityId] |= additionalMask;
		UpdateSystems(entityId, _entityComponents[entityId]);
	}

	template<typename T>
	inline T* GetSystem() {
		return (_systems.find(GetTypeHash<T>()) != _systems.end())
			? static_cast<T*>(_systems[GetTypeHash<T>()].get())
			: nullptr;
	}

private:
	void UpdateSystems(scEntityId entityId, scBitMask64 entityComponentMask) {
		if (_systems.empty())
			throw std::out_of_range("Register at least one System before adding or removing Components");

		// Notify each system that an Entity's ComponentMask changed
		for (auto const& pair : _systems) {
			auto const& system = pair.second;
			auto const& systemMask = system->GetSystemMask();
			// Check if the Entity's ComponentMask matches the System and add (or remove)
			if ((entityComponentMask & systemMask) == systemMask)
				system->AddEntity(entityId);
			else
				system->RemoveEntity(entityId);
		}
	}

	// ------------------- OTHER -------------------

public:
	inline size_t AvailableEntitiesSize() const { return _availableEntities.size(); }
	inline scUint32 GetSystemMaxSize() const { return _maxEntities; }

	~EntityComponentSystem() = default;

private:
	// Entity variables:
	const scUint32 _maxEntities;
	std::queue<scEntityId> _availableEntities;
	// Component variables: 
	std::vector<scBitMask64> _entityComponents;
	std::unordered_map<scHash, std::shared_ptr<IEntityComponentArray>> _componentWorld;
	// System variables:
	std::unordered_map<scHash, std::shared_ptr<System>> _systems;
};

}

#endif
