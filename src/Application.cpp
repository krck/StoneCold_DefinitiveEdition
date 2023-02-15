
#include "GameCore.hpp"

using namespace StoneCold::Core;

// $cmake -G "MinGW Makefiles" -B build/Release -DCMAKE_BUILD_TYPE=Release
// $cmake -G "MinGW Makefiles" -B build/Debug -DCMAKE_BUILD_TYPE=Debug

int main() {
	// Setup the game and start the main loop
	GameCore game;
	return (game.Initialize() ? game.Run() : -1);
}
