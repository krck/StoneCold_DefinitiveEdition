
#ifndef STONECOLD_CORE_GAMECORE_H
#define STONECOLD_CORE_GAMECORE_H

#include <stack>
#include <array>
#include <thread>
#include <chrono>
#include <functional>
#include <filesystem>
#include <windows.h>
#include "Enums.hpp"
#include "SfmlManager.hpp"
#include "AssetManager.hpp"
#include "MainMenuScene.hpp"
#include "GamePlayScene.hpp"
#include "SceneAction.hpp"

namespace StoneCold::Core {

using namespace StoneCold::Common;
using namespace StoneCold::Assets;
using namespace StoneCold::Scenes;

//
// This is the central Game class
// - Responsible for running the main game loop and quitting the game
// - Includes all common functionality that is used by all Scenes (Window handle, Asset manager handle, etc.)
// - Constructs, manages and changes Scenes
// 
class GameCore {
public:
	GameCore();
	GameCore(const GameCore&) = delete;
	GameCore& operator=(const GameCore&) = delete;

	//
	// Setup SFML and create all Managers and Scenes
	//
	bool Initialize();

	//
	// Run the games main-loop, handle the timer and FPS limiter 
	// and trigger the Engines Event, Update and Render functions
	//
	int Run();

	~GameCore() = default;

private:
	//
	// Scene management (creation and destruction) is private
	// Any Scene handling (swtiching or accessing Scene ptrs) is public
	//
	bool AddScene(SceneType type, std::shared_ptr<Scene>&& scene);
	void SetSceneActive(SceneType type);
	void SceneEventCallback(SceneEvent eventType, SceneType eventScene);

private:
	bool _globalEXIT;
	std::string _basePath;
	sf::RenderWindow* _window;
	// Managers
	SfmlManager _sfml;
	AssetManager _assetManager;
	// Scenes
	Scene* _activeScene;
	std::unordered_map<ActionMap, std::string> _actionMap;
	std::unordered_map<SceneType, std::shared_ptr<Scene>> _scenes;

};

}

#endif
