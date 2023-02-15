
/*

#include <iostream>
#include "EntityComponentManager.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

// -----------------------------------------------------------------------
// ---------------------------- TEST FUNCTIONS ---------------------------
// -----------------------------------------------------------------------

void TEST_AddEntity(EntityComponentManager& ecm, scUint32 addCount, const std::string& tagAddition = "") {
	const auto t1 = high_resolution_clock::now();

	for (scUint32 i = 0; i < addCount; i++) {
		ecm.AddEntity("test" + std::to_string(i) + tagAddition);
	}

	const auto t2 = high_resolution_clock::now();
	std::cout << "Time (Add " << std::to_string(addCount) << "): " << std::to_string(duration_cast<milliseconds>(t2 - t1).count()) << "ms" << std::endl;
	std::cout << "Check - MaxSize: " << ecm.GetMaxSize() << " / Elements added: " << addCount << " / FreeSize: " << ecm.GetFreeSize()  << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
}

void TEST_RemoveEntity(EntityComponentManager& ecm, scUint32 removeCount, scUint32 removeOffset = 0) {
	const auto t1 = high_resolution_clock::now();

	for (scUint32 i = removeOffset; i < (removeCount + removeOffset); i++) {
		ecm.RemoveEntity(i);
	}

	const auto t2 = high_resolution_clock::now();
	std::cout << "Time (Remove " << std::to_string(removeCount) << "): " << std::to_string(duration_cast<milliseconds>(t2 - t1).count()) << "ms" << std::endl;
	std::cout << "Check - MaxSize: " << ecm.GetMaxSize() << " / Elements removed: " << removeCount << " / FreeSize: " << ecm.GetFreeSize() << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
}


int main() {
	const scUint32 eSize = 10;
	EntityComponentManager ecm(eSize);

	// TEST_AddEntity(ecm, eSize, "-0");
	// TEST_RemoveEntity(ecm, 5, 2);
	// TEST_AddEntity(ecm, 2, "-1");
	// TEST_AddEntity(ecm, 3, "-2");
	// TEST_RemoveEntity(ecm, 1);

	const auto newEntity = ecm.AddEntity("new");
	ecm.AddComponent<CPosition>(newEntity, { true, 19.f, 123.f });
	ecm.AddComponent<CCollision>(newEntity, { true, 1.f, 2.f, 3.f, 4.f });
	ecm.RemoveComponent<CPosition>(newEntity);

	return 0;
}



*/