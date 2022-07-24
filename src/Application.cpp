
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

#include <Types.hpp>
using namespace StoneCold::Common;


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

	size_t AddEntity(const std::string& tag) {
		size_t entityId = GetNextFreeIndex();
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
	inline T& GetComponent(size_t entityId) { return std::get<std::vector<T>>(_entityComponents)[entityId]; }
	template<typename T>
	inline const T& GetComponent(size_t entityId) const { return std::get<std::vector<T>>(_entityComponents)[entityId]; }

	template<typename T>
	inline bool HasComponent(size_t entityId) const { return dynamic_cast<Component>(std::get<std::vector<T>>(_entityComponents)[entityId]).Active; }

	inline const std::string& GetTag(size_t entityId) const { return _entityTags[entityId]; }
	inline bool GetActive(size_t entityId) const { return _entityActive[entityId]; }

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
	size_t AddEntity(const std::string& tag) {
		size_t e = EntityMemoryPool::Instance().AddEntity(tag);
		_entities.push_back(e);
		_entitiesByTag[tag].push_back(e);
		return e;
	}

    template<typename T,typename... TArgs>
    T& AddComponent(size_t entityId, TArgs&&... mArgs) {
        auto& component = EntityMemoryPool::Instance().GetComponent<T>(entityId);
        component = T(std::forward<TArgs>(mArgs)...);
        component.Active = true;
        return component;
    }

    template<typename T>
    T& RemoveComponent(size_t entityId) {
        auto& component = EntityMemoryPool::Instance().GetComponent<T>(entityId);
        component.Active = false;
        return component;
    }

private:
	std::vector<size_t> _entities;
	std::map<std::string, std::vector<size_t>> _entitiesByTag;
};







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

class EntityComponentManager {
public:
	EntityComponentManager(scUint16 maxSize);
	EntityComponentManager(const EntityComponentManager&) = delete;
	EntityComponentManager& operator=(const EntityComponentManager&) = delete;

	// --------------------- ENTITY LOGIC -----------------------
	scEntityId AddEntity(const std::string& tag);
	void RemoveEntity(scEntityId entityId);

	bool GetActive(scEntityId entityId) const;
	const std::string& GetTag(scEntityId entityId) const;
	scSptr<std::vector<scEntityId>> GetEntities(const std::string& tag);

	// ----------------- ENTITY-COMPONENT LOGIC -----------------
	template<typename T> T& AddComponent(scEntityId entityId, T&& component);
    template<typename T> void RemoveComponent(scEntityId entityId);

	template<typename T> T& GetComponent(scEntityId entityId);
	template<typename T> const T& GetComponent(scEntityId entityId) const;
	template<typename T> bool HasComponent(scEntityId entityId) const;

	// -------------------- COMPONENT LOGIC ---------------------
	template<typename T> void RegisterComponentPool();
	template<typename T> bool HasComponentPool() const;

	~EntityComponentManager() = default;

private:
	const scUint16 _maxSize;
	std::stack<scEntityId> _availableEntities;
	// ----------- ENTITY MEMBERS -----------
	std::vector<bool> _entityActive;
	std::vector<std::string> _entityTags;
	std::vector<scEntityId> _entities;
	// std::map<std::string, std::vector<scEntityId>> _entitiesByTag;
	// --------- COMPONENT MEMBERS ----------
	std::tuple<
		std::vector<CPosition>,
		std::vector<CCollision>,
		std::vector<CHealth>
	> _entityComponentPools;

};














int main() {

	return 0;
}