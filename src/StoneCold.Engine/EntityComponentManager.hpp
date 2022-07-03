
#ifndef STONECOLD_ENTITYCOMPONENTMANAGER_H
#define STONECOLD_ENTITYCOMPONENTMANAGER_H

#include "SDL_Base.hpp"
#include "Settings.hpp"
#include "EntityComponentArray.hpp"
#include <typeindex>
#include <typeinfo>
#include <array>
#include <queue>

namespace StoneCold::Engine {

using namespace StoneCold::Base;

//
// Entity-Component Manager
// based on: https://austinmorlan.com/posts/entitycomponent_system/
//
// Managing the creation and destruction of Entities. This includes distributing
// Entity IDs and keeping record of which IDs are in use and which are not.
//
class EntityComponentManager {
public:
	EntityComponentManager()
		: _availableEntities(std::queue<entity>())
		, _entityComponents(std::array<mask, MAX_ENTITIES>())
		, _componentArrays(std::unordered_map<std::type_index, std::shared_ptr<IEntityComponentArray>>())
		, _componentMasks(std::unordered_map<std::type_index, mask>()) { }

	EntityComponentManager(const EntityComponentManager&) = delete;
	EntityComponentManager& operator=(const EntityComponentManager&) = delete;

	void Init() {
		// Initialize the queue with all possible entity IDs
		for (entity entity = 0; entity < MAX_ENTITIES; ++entity)
			_availableEntities.push(entity);

		// Add this component type to the component type map (hardcoded for each Component)
		_componentMasks.insert({ std::type_index(typeid(EntityComponentManager)),	0x0000000000000001 });
		_componentMasks.insert({ std::type_index(typeid(EntityComponentManager)),	0x0000000000000002 });
		_componentMasks.insert({ std::type_index(typeid(EntityComponentManager)),	0x0000000000000004 });
		_componentMasks.insert({ std::type_index(typeid(EntityComponentManager)),	0x0000000000000008 });
		_componentMasks.insert({ std::type_index(typeid(EntityComponentManager)),	0x0000000000000010 });
		_componentMasks.insert({ std::type_index(typeid(EntityComponentManager)),	0x0000000000000020 });
		// ...

		// Create a ComponentArray pointer and add it to the component arrays map (hardcoded for each Component)
		_componentArrays.insert({ std::type_index(typeid(EntityComponentManager)), std::make_shared<EntityComponentArray<EntityComponentManager>>() });
		_componentArrays.insert({ std::type_index(typeid(EntityComponentManager)), std::make_shared<EntityComponentArray<EntityComponentManager>>() });
		// ...
	}

	entity CreateEntity() {
		// Get the first available ID of the queue
		entity id = _availableEntities.front();
		_availableEntities.pop();
		// Reset the new Entities ComponentMask
		_entityComponents[id] = 0;
		return id;
	}

	void DestroyEntity(entity entity) {
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : _componentArrays) {
			auto const& component = pair.second;
			component->EntityDestroyed(entity); // INTERFACE IS NEEDED FOR THIS!
		}

		// Invalidate the destroyed entity's ComponentMask
		_entityComponents[entity] = 0;
		// Put the destroyed ID at the back of the queue
		_availableEntities.push(entity);
	}

	template<typename T>
	void AddComponent(entity entity, T component) {
		// Add a component to the array for an Entity and update the ComponentMask
		GetComponentArray<T>()->insert(entity, component);
		// SET FLAG: OR bitmask with the current value
		_entityComponents[entity] |= GetComponentMask<T>();
	}

	template<typename T>
	void RemoveComponent(entity entity) {
		// Remove a component from the array for an Entity and update the ComponentMask
		GetComponentArray<T>()->erase(entity);
		// REMOVE FLAG: AND with the inverse of the bitmask
		_entityComponents[entity] &= ~GetComponentMask<T>();
	}

	template<typename T>
	inline T& GetComponent(entity entity) { return GetComponentArray<T>()->GetData(entity); }

	template<typename T>
	inline mask GetComponentMask() { return _componentMasks[std::type_index(typeid(T))]; }

	inline mask GetEntityComponents(entity entity) const { return _entityComponents[entity]; }

	~EntityComponentManager() = default;

private:
	// Convenience function to get the statically casted pointer to the ComponentArray of type T.
	template<typename T>
	inline EntityComponentArray<T>* GetComponentArray() { return dynamic_cast<EntityComponentArray<T>*>(_componentArrays[std::type_index(typeid(T))].get()); }

private:
	// Entity variables
	std::queue<entity> _availableEntities;
	std::array<mask, MAX_ENTITIES> _entityComponents;
	// Component variables
	std::unordered_map<std::type_index, mask> _componentMasks;
	std::unordered_map<std::type_index, std::shared_ptr<IEntityComponentArray>> _componentArrays;
};

}

#endif
