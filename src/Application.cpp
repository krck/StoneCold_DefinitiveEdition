
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


/*
	EntityMemoryPool
	Main part of the ECS is the Memory pool. This pool has a fixed size of all possible entities and keeps a
	vector of that size for each component (Component Array), a vector with Entity Tags and a vector with a
	flag shwoing if a entity is active. The index of each vector are the assigned EntityIds

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

#include <map>
#include <tuple>
#include <vector>
#include <string>

using EntityId = size_t;

struct Component { bool Active = false; };
struct CPosition : public Component { int x; int y; };
struct CCollision : public Component { int width; int height; int x; int y; };
struct CHealth : public Component { int hp; };


class EntityMemoryPool {
public:
	static EntityMemoryPool& Instance() {
		static EntityMemoryPool pool(1000);
		return pool;
	}

	EntityId AddEntity(const std::string& tag) {
		EntityId entityId = GetNextFreeIndex();
		// Set all components to a default value
		std::get<std::vector<CPosition>>(_entityComponents)[entityId] = CPosition();
		std::get<std::vector<CCollision>>(_entityComponents)[entityId] = CCollision();
		std::get<std::vector<CHealth>>(_entityComponents)[entityId] = CHealth();
		// Set the tag and active flag
		_entityTags[entityId] = tag;
		_entityActive[entityId] = true;
		return entityId;
	}

	template<typename T>
	inline T& GetComponent(EntityId entityId) { return std::get<std::vector<T>>(_entityComponents)[entityId]; }
	template<typename T>
	inline const T& GetComponent(EntityId entityId) const { return std::get<std::vector<T>>(_entityComponents)[entityId]; }

	template<typename T>
	inline bool HasComponent(EntityId entityId) const { return dynamic_cast<Component>(std::get<std::vector<T>>(_entityComponents)[entityId]).Active; }

	inline const std::string& GetTag(EntityId entityId) const { return _entityTags[entityId]; }
	inline bool GetActive(EntityId entityId) const { return _entityActive[entityId]; }

private:
	EntityMemoryPool(size_t maxSize);

	size_t GetNextFreeIndex() { 
		// Get index of first entity that is not "active"
		// _entityActive[i] == false ?? use this 
	}

private:
	size_t _entityCount;
	std::vector<std::string> _entityTags;
	std::vector<bool> _entityActive;

	std::tuple<
		std::vector<CPosition>,
		std::vector<CCollision>,
		std::vector<CHealth>
	> _entityComponents;

}; 



class EntityManager {
public:
	EntityId AddEntity(const std::string& tag) {
		EntityId e = EntityMemoryPool::Instance().AddEntity(tag);
		_entities.push_back(e);
		_entitiesByTag[tag].push_back(e);
		return e;
	}

    template<typename T,typename... TArgs>
    T& AddComponent(EntityId entityId, TArgs&&... mArgs) {
        auto& component = EntityMemoryPool::Instance().GetComponent<T>(entityId);
        component = T(std::forward<TArgs>(mArgs)...);
        component.Active = true;
        return component;
    }

    template<typename T>
    T& RemoveComponent(EntityId entityId) {
        auto& component = EntityMemoryPool::Instance().GetComponent<T>(entityId);
        component.Active = false;
        return component;
    }

private:
	std::vector<EntityId> _entities;
	std::map<std::string, std::vector<EntityId>> _entitiesByTag;
};



int main() {

	return 0;
}