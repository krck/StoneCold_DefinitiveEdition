
#ifndef STONECOLD_CORE_GAMECORE_H
#define STONECOLD_CORE_GAMECORE_H

#include <stack>
#include <array>
#include <filesystem>
#include <windows.h>
#include "Enums.hpp"
// Managers
#include "SfmlManager.hpp"
#include "AssetManager.hpp"
// Scenes
#include "GamePlayScene.hpp"

namespace StoneCold::Core {

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

	//
	// Scene management (creation and destruction) is private
	// Any Scene handling (swtiching or accessing Scene ptrs) is public
	//
private:
	bool AddScene(SceneType type, std::shared_ptr<Scene>&& scene);
	bool RemoveScene(SceneType type);

public:
	void PushScene(SceneType type);
	void PopScene();

	inline Scene* GetActiveScene() { return _sceneStack.top(); }
	inline Scene* GetScene(SceneType type) { return _scenes[type].get(); }
	inline bool HasScene(SceneType type) const { return (_scenes.find(type) != _scenes.end()); }

	~GameCore() = default;

private:
	std::string _basePath;
	sf::RenderWindow* _window;
	// Managers
	SfmlManager _sfml;
	AssetManager _assetManager;
	// Scenes
	std::stack<Scene*> _sceneStack;
	std::unordered_map<SceneType, std::shared_ptr<Scene>> _scenes;

};

}

#endif
