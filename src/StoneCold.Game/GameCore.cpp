
#include "GameCore.hpp"

using namespace StoneCold::Game;
using namespace StoneCold::Resources;


GameCore::GameCore()
	: _sdl(SDLManager())
	, _engine(EngineCore())
	, _mapManager(MapManager())
	, _eventManager(EventManager::GetInstance())
	, _resources(ResourceManager())
	, _simulation(SimulationManager()) { };


bool GameCore::Initialize(const std::string& windowName) {
	try {
		// Init SDL will create and show the Application Window
		if (_sdl.InitializeSDL(windowName)) {
			// Get the SDL_Renderer and setup the Engine
			auto rendererPtr = _sdl.GetSDLRenderer();
			_engine.Initialize(rendererPtr);
			// Setup all the additional Managers in the correct order
			_resources.Initialize(rendererPtr);
			_simulation.Initialize(&_engine, rendererPtr, &_resources, &_mapManager);

			// Setup the randomizer with a seed
			std::srand(RNG_SEED);

			// Load all global Resources and create the basic States
			_simulation.CreateIntroState();
			_simulation.CreateGameState();
			_simulation.CreateMenuState();
			// Load a first Level and add it to the GameState
			_simulation.LoadLevel();

			// Push the first State to update and render
			auto firstState = _engine.GetState<IntroState>();
			_engine.PushState(firstState);

			return true;
		}
		else {
			return false;
		}
	}
	catch (const std::exception & ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
}


//
// Run the main Game-loop
//
int GameCore::Run() {
	try {
		// Setup timing and loop variables
		bool exit = false;
		bool printFPS = false;
		// Loop timer variables
		uint32 timeStamp_new = SDL_GetTicks();
		uint32 timeStamp_old = SDL_GetTicks();
		uint32 frameTime = 0; // delta in ms
		// FPS Counter variables
		const uint8 frameTimeSize = 20;
		auto frameTimes = std::array<uint32, frameTimeSize>();
		uint64 frameCount = 0;
		float averageFPS = 0.f;
		// Setup Event-Handling variables
		uint32 userEventType = _eventManager.UserEventType;
		auto keyStates = std::vector<uint8>();
		int numKeys = 0;
		SDL_Event event;

		// Start the main loop
		while (!exit) {
			timeStamp_new = SDL_GetTicks();
			frameTime = timeStamp_new - timeStamp_old;

			// Poll the event loop to gather events from input devices
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT)
					exit = true;

				// Toggle FPS output when F1 is pressed
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F1)
					printFPS = !printFPS;

				// Pass SDL Events on to the Engine/States and do nothing if it was handled there
				if (!_engine.HandleSDLEvent(event)) {
					// Handle the custom User-Events
					if (event.type == userEventType && event.user.code == EventCode::ChangeLevel) {
						// Load a new Level
						_simulation.LoadLevel();
					}
					else if (event.type == userEventType && event.user.code == EventCode::Quit) {
						// Quit the Application
						exit = true;
					}
				}
			}

			// Get a snapshot of the current state of the keyboard and handle the input
			const uint8* keyPtr = SDL_GetKeyboardState(&numKeys);
			keyStates = std::vector<uint8>(keyPtr, keyPtr + numKeys);

			// Engine core functions
			_engine.HandleInputEvent(keyStates);
			_engine.Update(frameTime);
			_engine.Render();

			// FPS counter (average)
			frameTimes[frameCount] = frameTime;
			frameCount++;
			if (frameCount == frameTimeSize) {
				frameCount = 0;
				averageFPS = 0.f;
				if (printFPS) {
					// In case it should be visible: Calculate and print the average FPS
					for (size_t i = 0; i < frameTimeSize; i++) {
						averageFPS += frameTimes[i];
					}

					averageFPS = 1000.f / (averageFPS / frameTimeSize);
					std::cout << "FPS: " << averageFPS << "\n";
				}
			}

			timeStamp_old = timeStamp_new;
		}
		return 0;
	}
	catch (const std::exception & ex) {
		std::cout << ex.what() << std::endl;
		return -1;
	}
}
