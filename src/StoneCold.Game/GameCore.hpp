
#ifndef STONECOLD_GAMECORE_H
#define STONECOLD_GAMECORE_H

#include "Settings.hpp"
#include "AiManager.hpp"
#include "SDLManager.hpp"
#include "EngineCore.hpp"
#include "MapManager.hpp"
#include "EventManager.hpp"
#include "ResourceManager.hpp"
#include "SimulationManager.hpp"
#include <array>

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

//
// This is the central Game class running the main-loop
//
class GameCore {
public:
	GameCore();
	GameCore(const GameCore&) = delete;
	GameCore& operator=(const GameCore&) = delete;

	//
	// Setup SDL, create all SDL Resources and show the Window
	// Also initilaizes the Engine and the Managers in order
	//
	bool Initialize(const std::string& windowName);

	//
	// Run the games main-loop, handle the timer and FPS limiter 
	// and trigger the Engines Event, Update and Render functions
	//
	int Run();

	~GameCore() = default;

private:
	SDLManager _sdl;
	EngineCore _engine;
	ResourceManager _resources;
	SimulationManager _simulation;
	EventManager& _eventManager;
	MapManager _mapManager;
	AiManager _aiManager;
};

}

#endif
