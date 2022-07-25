
/*

#include "GameCore.hpp"

using namespace StoneCold::Core;

// $cmake -G "MinGW Makefiles" -B build/Release -DCMAKE_BUILD_TYPE=Release
// $cmake -G "MinGW Makefiles" -B build/Debug -DCMAKE_BUILD_TYPE=Debug

int main() {
	// Setup the game and start the main loop
	GameCore game;
	return (game.Initialize() ? game.Run() : -1);
}


*/




#include <map>
#include <tuple>
#include <vector>
#include <stack>
#include <string>
#include "Types.hpp"
#include "Exception.hpp"

using namespace StoneCold::Common;

/*
	EntityComponentManager
	Main part of the ECS is the EntityComponentManager with Entity tracking and the Component memory pools. 

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

	- Components have a Active Flag
	- Entities have a Active Flag
	This allows for very quick "adding" and "removing" of Entities and theirs components, as only this flag 
	needsto be changed and the memory will be available and overwritten as soon as new Entity is added

*/


struct Component { bool Active = false; };
struct CPosition : public Component { int x; int y; };
struct CCollision : public Component { int width; int height; int x; int y; };
struct CHealth : public Component { int hp; };


class EntityComponentManager {
public:
	EntityComponentManager(scUint16 maxSize) 
		: _maxSize(maxSize)
		, _entityActive(std::vector<bool>(maxSize, false))
		, _entityTags(std::vector<std::string>(maxSize, "")) {
		// Initialize all the Component pools with default constructed components
		std::get<std::vector<CPosition>>(_entityComponentPools) = std::vector<CPosition>(maxSize, CPosition());
		std::get<std::vector<CCollision>>(_entityComponentPools) = std::vector<CCollision>(maxSize, CCollision());
		std::get<std::vector<CHealth>>(_entityComponentPools) = std::vector<CHealth>(maxSize, CHealth());
	}

	EntityComponentManager(const EntityComponentManager&) = delete;
	EntityComponentManager& operator=(const EntityComponentManager&) = delete;

	// ----------------------------------------------------------
	// --------------------- ENTITY LOGIC -----------------------
	// ----------------------------------------------------------

	scEntityId AddEntity(const std::string& tag) {
		scEntityId entityId = GetNextFreeIndex();
		_entityActive[entityId] = true;
		_entityTags[entityId] = tag;
		// Reset all components to a default constructed value
		// std::get<std::vector<CPosition>>(_entityComponentPools)[entityId] = CPosition();
		// std::get<std::vector<CCollision>>(_entityComponentPools)[entityId] = CCollision();
		// std::get<std::vector<CHealth>>(_entityComponentPools)[entityId] = CHealth();
		return entityId;
	}

	void RemoveEntity(scEntityId entityId) {
		_entityActive[entityId] = false;
		_entityTags[entityId] = "";
	}

	inline bool GetActive(scEntityId entityId) const { return _entityActive[entityId]; }
	inline const std::string& GetTag(scEntityId entityId) const { return _entityTags[entityId]; }
	//std::vector<scEntityId> GetEntities(const std::string& tag);

	// ----------------------------------------------------------
	// ----------------- ENTITY-COMPONENT LOGIC -----------------
	// ----------------------------------------------------------

	template<typename T> T& AddComponent(scEntityId entityId, T&& component) {
        auto& eComp = std::get<std::vector<T>>(_entityComponentPools)[entityId];
        eComp = std::move(component);
        eComp.Active = true;
        return eComp;
	}

	template<typename T> T& AddComponent(scEntityId entityId, const T& component) {
        auto& eComp = std::get<std::vector<T>>(_entityComponentPools)[entityId];
        eComp = component;
        eComp.Active = true;
        return eComp;
	}

    template<typename T> void RemoveComponent(scEntityId entityId) {
        auto& eComp = std::get<std::vector<T>>(_entityComponentPools)[entityId];
        eComp.Active = false;
	}

	template<typename T> inline T& GetComponent(scEntityId entityId) { return std::get<std::vector<T>>(_entityComponentPools)[entityId]; }
	template<typename T> inline const T& GetComponent(scEntityId entityId) const { return std::get<std::vector<T>>(_entityComponentPools)[entityId]; }
	template<typename T> inline bool HasComponent(scEntityId entityId) const  { return std::get<std::vector<T>>(_entityComponentPools)[entityId].Active; }

	~EntityComponentManager() = default;

private:
	scEntityId GetNextFreeIndex() {
		for (size_t i = 0; i < _entityActive.size(); i++) {
			if(!_entityActive[i]) return i;
		}
		throw GameException("No more Entity Ids available. Max: " + _maxSize);
	}

private:
	const scUint16 _maxSize;
	// ----------- ENTITY MEMBERS -----------
	std::vector<bool> _entityActive;
	std::vector<std::string> _entityTags;
	// std::map<std::string, std::vector<scEntityId>> _entitiesByTag;
	// --------- COMPONENT MEMBERS ----------
	std::tuple<
		std::vector<CPosition>,
		std::vector<CCollision>,
		std::vector<CHealth>
	> _entityComponentPools;

};




int main() {
	EntityComponentManager ecm(10);
 
	return 0;
}