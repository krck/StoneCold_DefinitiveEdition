
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
	(This implementation trades memory cache optimization for some quicker adding and removing of entities)

					 Entity 0			Entity 1			Entity 2
				________________________________________________________________________
				|				 	|				 	|				 	|
	CPosition	|  x:7 y:5 a:TRUE 	|  x:2 y:2 a:TRUE 	|  x:0 y:0 a:FALSE 	|
				|___________________|___________________|___________________|_____ ...
				|					|					|					|
	CHealth		|	hp:500 a:TURE	|	hp:0 a:FALSE	|	hp:0 a:FALSE	|
				|___________________|___________________|___________________|_____ ...
				|
				...
				|___________________|___________________|___________________|_____ ...
	Tag			|______PLAYER_______|_______TILE________|___________________|_____ ...
	Active		|_______TRUE________|_______TRUE________|______FALSE________|_____ ...

	Simplicity and speed based on:
	- Entities have a Active Flag
	- Components have a Active Flag
	This allows for very quick "adding" and "removing" of Entities and theirs components, as only this flag
	needsto be changed and the memory will be available and overwritten as soon as new Entity is added
*/

class EntityComponentManager {
public:
	EntityComponentManager(scUint32 maxSize)
		: _maxSize(maxSize)
		, _availableIds(std::queue<scEntityId>())
		, _entityActive(std::vector<bool>(maxSize, false))
		, _entityTags(std::vector<std::string>(maxSize, "")) {
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

	inline scUint32 GetMaxSize() { return _maxSize; }
	inline scUint32 GetFreeSize() { return _availableIds.size(); }

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
		_availableIds.push(entityId);
	}

	inline bool GetActive(scEntityId entityId) { return _entityActive[entityId]; }
	inline const std::string& GetTag(scEntityId entityId) const { return _entityTags[entityId]; }

	// ----------------------------------------------------------
	// ----------------- ENTITY-COMPONENT LOGIC -----------------
	// ----------------------------------------------------------

	template<typename T> T& AddComponent(scEntityId entityId, T&& component) {
		auto& eComp = std::get<std::vector<T>>(_entityComponentPools)[entityId];
		eComp = std::move(component);
		eComp.Active = true;
		return eComp;
	}

	template<typename T> void RemoveComponent(scEntityId entityId) {
		// !!!! Might remove if this becomes to costly / Just set Active = false !!!!
		std::get<std::vector<T>>(_entityComponentPools)[entityId] = T();
	}

	template<typename T> inline T& GetComponent(scEntityId entityId) { return std::get<std::vector<T>>(_entityComponentPools)[entityId]; }
	template<typename T> inline const T& GetComponent(scEntityId entityId) const { return std::get<std::vector<T>>(_entityComponentPools)[entityId]; }
	template<typename T> inline bool HasComponent(scEntityId entityId) { return std::get<std::vector<T>>(_entityComponentPools)[entityId].Active; }

private:
	const scUint32 _maxSize;
	std::queue<scEntityId> _availableIds;
	// ----------- ENTITY MEMBERS -----------
	std::vector<bool> _entityActive;
	std::vector<std::string> _entityTags;
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

};

}

#endif
