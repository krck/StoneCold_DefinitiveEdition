
#include "GameCore.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Assets;
using namespace StoneCold::Scenes;

GameCore::GameCore()
	: _sfml(SfmlManager())
	, _assetManager(AssetManager())
	, _sceneStack(std::stack<Scene*>())
	, _scenes(std::unordered_map<SceneType, std::shared_ptr<Scene>>()) 
	{ };

bool GameCore::Initialize() {
	try {
		// Get the current path to the running .exe
		// (When NULL is passed to GetModuleHandle, the handle of the exe itself is returned)
        wchar_t fsPathRaw[MAX_PATH];
        GetModuleFileNameW(NULL, fsPathRaw, MAX_PATH);
        _basePath = std::filesystem::path(fsPathRaw).parent_path().u8string();

		// Init will create and show the Application Window
		if(_assetManager.Initialize(_basePath) && _sfml.Initialize(_assetManager)) {
			// Set the now active render window
			_window = _sfml.GetWindow();

			AddScene(SceneType::GamePlay, std::make_shared<GamePlayScene>(20000, _assetManager));
			PushScene(SceneType::GamePlay);


			/*
			// Setup all the additional Managers in the correct order
			_engine.Initialize(rendererPtr);
			_resources.Initialize(rendererPtr);
			_simulation.Initialize(&_engine, rendererPtr, &_resources, &_mapManager);

			// Setup the randomizer with a seed
			std::srand(RNG_SEED);

			// Load all global Resources and create the basic States
			_simulation.CreateIntroState();
			_simulation.CreateGamePlayScene();
			_simulation.CreateMenuState();
			// Load a first Level and add it to the GamePlayScene
			_simulation.LoadLevel();

			// Push the first State to update and render
			auto firstState = _engine.GetState<IntroState>();
			_engine.PushState(firstState);
			*/
			return true;
		}
		return false;
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
		sf::Clock clock; // Starts the clock
		sf::Event event;

		// Setup timing and loop variables
		bool exit = false;
		bool showFPS = true;
		// Loop timer variables
		scInt32 frameTime = 0; // delta in ms
		scInt64 frameCount = 0;
		const scUint8 frameCountMax = 40;
		auto frameTimes = std::array<scUint32, frameCountMax>();
		float averageFPS = 0.f;

		// Start the main loop
		while (!exit) {
			// Clock restart returns the elapsed (frame)time
			frameTime = clock.restart().asMilliseconds();

			// Poll the event loop to gather events from input devices
			while (_window->pollEvent(event)) {
				if (event.type == sf::Event::Closed) { 
					exit = true; 
					if (!_sceneStack.empty()) {
						_sceneStack.top()->Stop();
					}
				}

				else if (event.type == sf::Event::Resized) { /* Resize from user changes to the window, or from setting it in code */}
				else if (event.type == sf::Event::LostFocus) { /* _engine.pause(); */ }
				else if (event.type == sf::Event::GainedFocus) { /* _engine.resume(); */ }
				
				else if (event.type == sf::Event::TextEntered)
				{
					// TextEntered differs from KeyPressed Events, as it contains a "full" user input if possible
					// Example: Pressing '^' then 'e' on a French keyboard will produce two KeyPressed events, but a single TextEntered 'ê' character
					// Use TextEntered in Textboxes (whenever a user has to enter actual Text)
				}
				
				/*
				// Toggle FPS output when F1 is pressed
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F1)
					showFPS = !showFPS;

				// Pass SDL Events on to the Engine/States and do nothing if it was handled there
				if (!_sceneStack.top()->HandleSDLEvent(sdlEvent);) {
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
				*/
			}

			// Use sf::Keyboard.isKeyPressed() for the most "direct" input handling
			// (The events sf::Event::KeyPressed and sf::Event::KeyReleased have some delay or require additional code to "smoothen" this. Eg.: KeyServer/Client)

			// Core functions (currentScene should never be null)
			// Reset screen, Handle input, Update entities, Render and display
        	_window->clear(sf::Color::Black);
			if(!_sceneStack.empty()) {
				_sceneStack.top()->HandleInput();
				_sceneStack.top()->Update(frameTime); 
				_sceneStack.top()->Render(_window);
			}
        	_window->display();

			// FPS counter (average)
			frameTimes[frameCount++] = frameTime;
			if (frameCount == frameCountMax) {
				frameCount = 0;
				averageFPS = 0.f;
				if (showFPS) {
					// In case it should be visible: Calculate and print the average FPS
					for (size_t i = 0; i < frameCountMax; i++) {
						averageFPS += frameTimes[i];
					}

					averageFPS = 1000.f / (averageFPS / frameCountMax);
					std::cout << "FPS: " << averageFPS << "\n";
				}
			}
		}
		_window->close();

		return 0;
	}
	catch (const std::exception & ex) {
		std::cout << ex.what() << std::endl;
		return -1;
	}
}

// -------------------------- SCENE CODE --------------------------

bool GameCore::AddScene(SceneType type, std::shared_ptr<Scene>&& scene) { 
	_scenes[type] = std::move(scene); 
	return _scenes[type]->Initialize();
}

void GameCore::PushScene(SceneType type) {
	// If the selected Scene is unknown, dont switch
	if (_scenes.find(type) == _scenes.end())
		return;

	// Stop the current Scene
	if (!_sceneStack.empty()) {
		_sceneStack.top()->Stop();
	}
	// Push and start the new Scene
	_sceneStack.push(_scenes[type].get());
	_sceneStack.top()->Start();
}

void GameCore::PopScene() {
	// Stop and pop the current scene
	if (!_sceneStack.empty()) {
		_sceneStack.top()->Stop();
		_sceneStack.pop();
	}
	// Start previous scene again
	if (!_sceneStack.empty()) {
		_sceneStack.top()->Start();
	}
}

bool GameCore::RemoveScene(SceneType type) {
	auto sceneIter = _scenes.find(type);
	if (sceneIter != _scenes.end()) {
		sceneIter->second->Stop();
		_scenes.erase(type);
		return true;
	}
	return false;
}
