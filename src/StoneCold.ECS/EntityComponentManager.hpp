
#ifndef STONECOLD_ECS_ENTITYCOMPONENTMANAGER_H
#define STONECOLD_ECS_ENTITYCOMPONENTMANAGER_H

#include <tuple>
#include <vector>
#include <queue>
#include <string>
#include <chrono>
#include <utility>
#include "Types.hpp"
#include "Components.hpp"

namespace StoneCold::ECS {

using namespace StoneCold::Common;

/*
	EntityComponentManager
	Main part of the ECS is the EntityComponentManager with Entity tracking and the Component memory pools.

	This specific implementation (Entity has an "Active" bool and Component is just an "Active" bit) sacrifices a bit of
	cache-coherency (meaning: speed on looping and manipulating components) for more speed when it comes to adding and
	removing both entities and components.

							 Entity 0			  Entity 1			  Entity 2
						________________________________________________________________________
						|				 	|				 	|				 	|
	CPosition			|  x:7 y:5 a:TRUE 	|  x:2 y:2 a:TRUE 	|  x:0 y:0 a:FALSE 	|
						|___________________|___________________|___________________|_____ ...
						|					|					|					|
	CHealth				|	hp:500 a:TURE	|	hp:0 a:FALSE	|	hp:0 a:FALSE	|
						|___________________|___________________|___________________|_____ ...
						|
						...
						|___________________|___________________|___________________|_____ ...
	Entity Active		|_______TRUE________|_______TRUE________|______FALSE________|_____ ...
	Entity Tag			|______PLAYER_______|_______TILE________|___________________|_____ ...
	Component Bitmask	|_______0011________|_______0001________|_______0000________|_____ ...

	Components are not stored in any "packed" data container where they can be looped without cache-misses, instead they are
	stored in a simple vector and are added and removed manily by setting the Bit Mask on the entity. But that will !! leave 
	"gaps" when looping components. This might not be completley in line with the general ECS "Cache-optimization" principal,
	but it removes so much complexity on data containers, that its generally faster than the old "packed-array" versions.

*/

class EntityComponentManager {
public:
	EntityComponentManager(scUint32 maxSize)
		: _maxSize(maxSize)
		, _availableIds(std::queue<scEntityId>())
		, _entityActive(std::vector<bool>(maxSize, false))
		, _entityTags(std::vector<std::string>(maxSize, ""))
		, _entityComponentMasks(std::vector<scBitMask64>(maxSize, 0)) {
		// Initialize all the Component pools with default constructed components
		std::get<std::vector<CInput>>(_entityComponentPools) = std::vector<CInput>(maxSize, CInput());
		std::get<std::vector<CPosition>>(_entityComponentPools) = std::vector<CPosition>(maxSize, CPosition());
		std::get<std::vector<CTransform>>(_entityComponentPools) = std::vector<CTransform>(maxSize, CTransform());
		std::get<std::vector<CStatic>>(_entityComponentPools) = std::vector<CStatic>(maxSize, CStatic());
		std::get<std::vector<CSprite>>(_entityComponentPools) = std::vector<CSprite>(maxSize, CSprite());
		std::get<std::vector<CAnimation>>(_entityComponentPools) = std::vector<CAnimation>(maxSize, CAnimation());
		std::get<std::vector<CBoundingBox>>(_entityComponentPools) = std::vector<CBoundingBox>(maxSize, CBoundingBox());
		// Loop to add each id to the "available" queue
		for (scUint32 i = 0; i < maxSize; i++) {
			_availableIds.push(i);
		}
	}

	EntityComponentManager(const EntityComponentManager&) = delete;
	EntityComponentManager& operator=(const EntityComponentManager&) = delete;

	inline scUint32 GetMaxSize() noexcept { return _maxSize; }
	inline scUint32 GetAvailableSize() noexcept { return _availableIds.size(); }

	~EntityComponentManager() = default;

	// ----------------------------------------------------------
	// --------------------- ENTITY LOGIC -----------------------
	// ----------------------------------------------------------

	scEntityId AddEntity(const std::string& tag) {
		scEntityId entityId = _availableIds.front();
		_entityActive[entityId] = true;
		_entityTags[entityId] = tag;
		_availableIds.pop();
		// Reset all components to a default constructed value
		// !!!!!! Might remove if this becomes to costly !!!!!!
		std::get<std::vector<CInput>>(_entityComponentPools)[entityId] = CInput();
		std::get<std::vector<CPosition>>(_entityComponentPools)[entityId] = CPosition();
		std::get<std::vector<CTransform>>(_entityComponentPools)[entityId] = CTransform();
		std::get<std::vector<CStatic>>(_entityComponentPools)[entityId] = CStatic();
		std::get<std::vector<CSprite>>(_entityComponentPools)[entityId] = CSprite();
		std::get<std::vector<CAnimation>>(_entityComponentPools)[entityId] = CAnimation();
		std::get<std::vector<CBoundingBox>>(_entityComponentPools)[entityId] = CBoundingBox();
		return entityId;
	}

	void RemoveEntity(scEntityId entityId) {
		_entityActive[entityId] = false;
		_entityTags[entityId] = "";
		_entityComponentMasks[entityId] = 0;
		_availableIds.push(entityId);
	}

	inline bool GetEntityActive(scEntityId entityId) { return _entityActive[entityId]; }
	inline const std::string& GetEntityTag(scEntityId entityId) const { return _entityTags[entityId]; }
	inline scBitMask64 GetEntityComponentMask(scEntityId entityId) const { return _entityComponentMasks[entityId]; }

	std::vector<scEntityId> GetEntitiesByComponents(const scBitMask64& componentMask) {
		std::vector<scEntityId> tmpVec;
		tmpVec.reserve(_maxSize - _availableIds.size());
		for (scUint32 e = 0; e < _maxSize; e++) {
			if ((_entityComponentMasks[e] & componentMask) == componentMask)
				tmpVec.push_back(e);
		}
		return tmpVec;
	}

	// ----------------------------------------------------------
	// ----------------- ENTITY-COMPONENT LOGIC -----------------
	// ----------------------------------------------------------

	template<typename T> T& AddComponent(scEntityId entityId, T&& component) {
		auto& eComp = std::get<std::vector<T>>(_entityComponentPools)[entityId];
		eComp = std::move(component);
		// Add the Component Flag to the mask (OR bitmask with the current value)
		_entityComponentMasks[entityId] |= _componentMasks[typeid(T)];
		return eComp;
	}

	template<typename T> void RemoveComponent(scEntityId entityId) {
		std::get<std::vector<T>>(_entityComponentPools)[entityId] = T();
		// Remove the Component Flag from the mask (AND with the inverse of the bitmask)
		_entityComponentMasks[entityId] &= ~_componentMasks[typeid(T)];
	}

	template<typename T> inline T& GetComponent(scEntityId entityId) { return std::get<std::vector<T>>(_entityComponentPools)[entityId]; }
	template<typename T> inline const T& GetComponent(scEntityId entityId) const { return std::get<std::vector<T>>(_entityComponentPools)[entityId]; }
	template<typename T> inline bool HasComponent(scEntityId entityId) { return ((_entityComponentMasks[entityId] & _componentMasks[typeid(T)]) == _componentMasks[typeid(T)]); }

	template<typename T> inline scBitMask32 GetComponentMask() { return _componentMasks[typeid(T)]; }

private:
	const scUint32 _maxSize;
	std::queue<scEntityId> _availableIds;
	// ----------- ENTITY MEMBERS -----------
	std::vector<bool> _entityActive;
	std::vector<std::string> _entityTags;
	std::vector<scBitMask64> _entityComponentMasks;
	// --------- COMPONENT MEMBERS ----------
	std::tuple<
		std::vector<CInput>,
		std::vector<CPosition>,
		std::vector<CTransform>,
		std::vector<CStatic>,
		std::vector<CSprite>,
		std::vector<CAnimation>,
		std::vector<CBoundingBox>
	> _entityComponentPools;
	// ---------- COMPONENT MASKS -----------
	std::unordered_map<std::type_index, const scBitMask64> _componentMasks = std::unordered_map<std::type_index, const scBitMask64>({
		{ typeid(CInput),			0x0000000000000001 },
		{ typeid(CPosition),		0x0000000000000002 },
		{ typeid(CTransform),		0x0000000000000004 },
		{ typeid(CStatic),			0x0000000000000008 },
		{ typeid(CSprite),			0x0000000000000010 },
		{ typeid(CAnimation),		0x0000000000000020 },
		{ typeid(CBoundingBox),		0x0000000000000040 },
	});

};

}

#endif
