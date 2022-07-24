
#include "GameCore.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Common;
using namespace StoneCold::Assets;
using namespace StoneCold::Scenes;

 GameCore::GameCore()
	: _globalEXIT(false)
	, _sfml(SfmlManager())
	, _assetManager(AssetManager())
	, _activeScene(nullptr)
	, _actionMap(std::unordered_map<ActionMap, std::string>())
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

			// Read the ActionMap Settings, used by the Scenes as Input mapping, from the json
			for(const auto& item : _assetManager.GetSettingsJson()["actionMap"].items()) {
				const int id = item.value()["id"].get<int>();
				const std::string name = item.value()["enumName"].get<std::string>();
				const std::string action = item.value()["action"].get<std::string>();
				if(action != "") {
					_actionMap.insert({ (ActionMap)id, action});
				}
			};

			AddScene(SceneType::MainMenu, std::make_shared<MainMenuScene>(10, _assetManager, _window));
			AddScene(SceneType::GamePlay, std::make_shared<GamePlayScene>(20000, _assetManager, _window));
			SetSceneActive(SceneType::MainMenu);

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
		bool windowHasFocus = true;
		// FPS limiter
		const float fpsLimit = _assetManager.GetSettingsJson()["window"]["maxFps"].get<float>();
		const scUint32 msPerFrame = 1000.f / fpsLimit;
		scUint32 frameElapsedMs; // always one frame behind
		// FPS calculation variables
		scInt32 frameCount = 0;
		const scUint8 frameCountMax = 60;
		auto frameTimes = std::array<scUint32, frameCountMax>();
		float averageFPS = 0.f;

		// Start the main loop
		while (!_globalEXIT) {
			// Get the current frame start time in ms (use "steady_clock")
			const auto frameStart = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());

			// Poll the event loop to gather events from input devices
			_activeScene->ClearActions();
			while (_window->pollEvent(event)) {
				if (event.type == sf::Event::Closed) { 
					_globalEXIT = true; 
					if (_activeScene != nullptr) {
						_activeScene->Stop();
					}
				}
				// On focus changes, set a bool to stop the Input/Update/Render cycle
				else if (event.type == sf::Event::LostFocus) { windowHasFocus = false; }
				else if (event.type == sf::Event::GainedFocus) { windowHasFocus = true; }

				// Check if "Start" or "End" action (based on Pressed/Released) and send the Action to the Scene
				// (Keycode mappings between any Keyboard Action and sf::Keyboard use the same IDs, so event.key.code can be used 1:1)
				else if(event.type == sf::Event::KeyPressed && _actionMap.find((ActionMap)event.key.code) != _actionMap.end()) {
					_activeScene->RegisterAction(SceneAction((ActionMap)event.key.code, ActionType::Start, _actionMap[(ActionMap)event.key.code]));
				}
				else if(event.type == sf::Event::KeyReleased && _actionMap.find((ActionMap)event.key.code) != _actionMap.end()) {
					_activeScene->RegisterAction(SceneAction((ActionMap)event.key.code, ActionType::End, _actionMap[(ActionMap)event.key.code]));
				}
				// Update the Mouse Actions
				else if (event.type == sf::Event::MouseButtonPressed) {
					if(event.mouseButton.button == sf::Mouse::Left && _actionMap.find(ActionMap::Mouse_Left) != _actionMap.end())
						_activeScene->RegisterAction(SceneAction(ActionMap::Mouse_Left, ActionType::Start, _actionMap[ActionMap::Mouse_Left]));
					if(event.mouseButton.button == sf::Mouse::Right && _actionMap.find(ActionMap::Mouse_Right) != _actionMap.end())
						_activeScene->RegisterAction(SceneAction(ActionMap::Mouse_Right, ActionType::Start, _actionMap[ActionMap::Mouse_Right]));
				}
				else if (event.type == sf::Event::MouseButtonReleased) {
					if(event.mouseButton.button == sf::Mouse::Left && _actionMap.find(ActionMap::Mouse_Left) != _actionMap.end())
						_activeScene->RegisterAction(SceneAction(ActionMap::Mouse_Left, ActionType::End, _actionMap[ActionMap::Mouse_Left]));
					if(event.mouseButton.button == sf::Mouse::Right && _actionMap.find(ActionMap::Mouse_Right) != _actionMap.end())
						_activeScene->RegisterAction(SceneAction(ActionMap::Mouse_Right, ActionType::End, _actionMap[ActionMap::Mouse_Right]));
				}
				else if (event.type == sf::Event::MouseMoved && _actionMap.find(ActionMap::Mouse_Moved) != _actionMap.end()) {
					_activeScene->RegisterAction(SceneAction(ActionMap::Mouse_Moved, ActionType::Start, _actionMap[ActionMap::Mouse_Moved]));
				}
				else if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					if(event.mouseWheelScroll.delta < 0 && _actionMap.find(ActionMap::Mouse_ScrolledUp) != _actionMap.end())
						_activeScene->RegisterAction(SceneAction(ActionMap::Mouse_ScrolledUp, ActionType::Start, _actionMap[ActionMap::Mouse_ScrolledUp]));
					if(event.mouseWheelScroll.delta > 0 && _actionMap.find(ActionMap::Mouse_ScrolledDown) != _actionMap.end())
						_activeScene->RegisterAction(SceneAction(ActionMap::Mouse_ScrolledDown, ActionType::Start, _actionMap[ActionMap::Mouse_ScrolledDown]));						
				}
				// Other Input Events
				else if (event.type == sf::Event::TextEntered) {
					// TextEntered differs from KeyPressed Events, as it contains a "full" user input if possible
					// Example: Pressing '^' then 'e' on a French keyboard will produce two KeyPressed events, but a single TextEntered 'ê' character
					// Use TextEntered in Textboxes (whenever a user has to enter actual Text)
				}

				// Finally, pass the event to the current Scene in case it has some specific logic (example: Resize)
				_activeScene->HandleEvent(event);
			}

			// Core functions (currentScene should never be null)
			// Reset screen, Handle input, Update entities, Render and display
			if(windowHasFocus) {
				// Engine Input/Update/Render cycle
				_window->clear(sf::Color::Black);
				_activeScene->HandleInput(_window);
				_activeScene->Update(frameElapsedMs); 
				_activeScene->Render();
				_window->display();

				// -------------------------------------------------------------------------
				// FPS counter (average)
				frameTimes[frameCount++] = frameElapsedMs;
				if (frameCount == frameCountMax) {
					frameCount = 0;
					averageFPS = 0.f;
					// In case it should be visible: Calculate and print the average FPS
					for (size_t i = 0; i < frameCountMax; i++) {
						averageFPS += frameTimes[i];
					}

					averageFPS = 1000.f / (averageFPS / frameCountMax);
					//std::cout << "FPS: " << (scUint16)averageFPS << "\n";
				}
				// -------------------------------------------------------------------------
			}

			// Limit FPS by waiting in case the current frame time is below the limit
			const auto frameEnd = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
			frameElapsedMs = (frameEnd - frameStart).count();
			if(frameElapsedMs < msPerFrame) {
				std::this_thread::sleep_for(std::chrono::milliseconds(msPerFrame - frameElapsedMs));
			}
			std::cout <<frameElapsedMs <<std::endl;
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

void GameCore::SetSceneActive(SceneType type) {
	// If the selected Scene is unknown, dont switch
	if (_scenes.find(type) == _scenes.end())
		return;

	// Stop the current Scene
	if (_activeScene != nullptr) {
		_activeScene->Stop();
	}
	// Push and start the new Scene
	_activeScene = _scenes[type].get();
	_activeScene->Start();
	_activeScene->SetSceneEventCallback(std::bind(&GameCore::SceneEventCallback, this, std::placeholders::_1, std::placeholders::_2));
}

void GameCore::SceneEventCallback(SceneEvent eventType, SceneType eventScene) {
	if(eventType == SceneEvent::QuitGame) {
		_globalEXIT = true; 
		if (_activeScene != nullptr) {
			_activeScene->Stop();
		}
	}
	else if(eventType == SceneEvent::ChangeScene) {
		SetSceneActive(eventScene);
	}
}
