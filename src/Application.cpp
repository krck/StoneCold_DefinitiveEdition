
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





#include <tuple>
#include <vector>
#include <queue>
#include <string>
#include <chrono>

#include <iostream>

using scUint8 = std::uint_fast8_t;
using scUint16 = std::uint_fast16_t;
using scUint32 = std::uint_fast32_t;
using scUint64 = std::uint_fast64_t;
using scEntityId = std::uint_fast16_t;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;


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
struct CPosition : public Component { float x = 0.f; float y = 0.f; };
struct CCollision : public Component { float width = 0.f; float height = 0.f; float x = 0.f; float y = 0.f; };
struct CHealth : public Component { float hp = 0.f; std::vector<float> data = std::vector<float>(); };


class EntityComponentManager {
public:
	EntityComponentManager(scUint16 maxSize)
		: _maxSize(maxSize)
		, _availableIds(std::queue<scEntityId>())
		, _entityActive(std::vector<bool>(maxSize, false))
		, _entityTags(std::vector<std::string>(maxSize, "")) {
		// Initialize all the Component pools with default constructed components
		std::get<std::vector<CPosition>>(_entityComponentPools) = std::vector<CPosition>(maxSize, CPosition());
		std::get<std::vector<CCollision>>(_entityComponentPools) = std::vector<CCollision>(maxSize, CCollision());
		std::get<std::vector<CHealth>>(_entityComponentPools) = std::vector<CHealth>(maxSize, CHealth());
		// Loop to add each id to the "available" queue
		for (scUint16 i = 0; i < maxSize; i++) {
			_availableIds.push(i);
		}
	}

	EntityComponentManager(const EntityComponentManager&) = delete;
	EntityComponentManager& operator=(const EntityComponentManager&) = delete;

	inline scUint16 GetMaxSize() { return _maxSize; }
	inline scUint16 GetFreeSize() { return _availableIds.size(); }

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
		// std::get<std::vector<CPosition>>(_entityComponentPools)[entityId] = CPosition();
		// std::get<std::vector<CCollision>>(_entityComponentPools)[entityId] = CCollision();
		// std::get<std::vector<CHealth>>(_entityComponentPools)[entityId] = CHealth();
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
	template<typename T> inline bool HasComponent(scEntityId entityId) { return std::get<std::vector<T>>(_entityComponentPools)[entityId].Active; }

private:
	const scUint16 _maxSize;
	std::queue<scEntityId> _availableIds;
	// ----------- ENTITY MEMBERS -----------
	std::vector<bool> _entityActive;
	std::vector<std::string> _entityTags;
	// --------- COMPONENT MEMBERS ----------
	std::tuple<
		std::vector<CPosition>,
		std::vector<CCollision>,
		std::vector<CHealth>
	> _entityComponentPools;

};





// -----------------------------------------------------------------------
// ---------------------------- TEST FUNCTIONS ---------------------------
// -----------------------------------------------------------------------

void TEST_AddEntity(EntityComponentManager& ecm, int addCount, const std::string& tagAddition = "") {
	const auto t1 = high_resolution_clock::now();

	for (size_t i = 0; i < addCount; i++) {
		ecm.AddEntity("test" + std::to_string(i) + tagAddition);
	}

	const auto t2 = high_resolution_clock::now();
	std::cout << "Time (Add " << std::to_string(addCount) << "): " << std::to_string(duration_cast<milliseconds>(t2 - t1).count()) << "ms" << std::endl;
	std::cout << "Check - MaxSize: " << ecm.GetMaxSize() << " / Elements added: " << addCount << " / FreeSize: " << ecm.GetFreeSize()  << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
}

void TEST_RemoveEntity(EntityComponentManager& ecm, int removeCount, int removeOffset = 0) {
	const auto t1 = high_resolution_clock::now();

	for (size_t i = removeOffset; i < (removeCount + removeOffset); i++) {
		ecm.RemoveEntity(i);
	}

	const auto t2 = high_resolution_clock::now();
	std::cout << "Time (Remove " << std::to_string(removeCount) << "): " << std::to_string(duration_cast<milliseconds>(t2 - t1).count()) << "ms" << std::endl;
	std::cout << "Check - MaxSize: " << ecm.GetMaxSize() << " / Elements removed: " << removeCount << " / FreeSize: " << ecm.GetFreeSize() << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
}



int main() {
	const int eSize = 10;
	EntityComponentManager ecm(eSize);

	TEST_AddEntity(ecm, eSize, "-0");
	TEST_RemoveEntity(ecm, 5, 2);
	TEST_AddEntity(ecm, 2, "-1");
	TEST_AddEntity(ecm, 3, "-2");
	TEST_RemoveEntity(ecm, 1);

	const auto newEntity = ecm.AddEntity("new");
	ecm.AddComponent<CPosition>(newEntity, { true, 19.f, 123.f });


	return 0;
}
