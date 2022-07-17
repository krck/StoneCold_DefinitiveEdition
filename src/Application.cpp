
#include "GameCore.hpp"

using namespace StoneCold::Core;

// $cmake -G "MinGW Makefiles" -B build/Release -DCMAKE_BUILD_TYPE=Release
// $cmake -G "MinGW Makefiles" -B build/Debug -DCMAKE_BUILD_TYPE=Debug

int main() {
	// Setup the game and start the main loop
	GameCore game;
	return (game.Initialize() ? game.Run() : -1);
}


/*
	- In general, try to use addition, subtraction and multiplication. division and square root are quite slow (sqrt is very slow even!)

	High level structure:
	
	GameEngine Architecture:
	- Scene (MainMenu-Scene, Gameplay-Scene, etc.)
		- Systems (Systems on a per-scene-basis. Eg. Gameplay needs a Physics-System, Menu does not)
		- EntityManager (EntityManager on a per-scene-basis. Manage Lifetime of Entities like Buttons or Enimies. Create and destroy.)
			- Create Entities (For Iterator protection, add entity at the beginning of the next frame)
			- Destroy Entities (For Iterator protection, flag entity as delete and then delete them the next frame)
			- Entity
				- Components

*/