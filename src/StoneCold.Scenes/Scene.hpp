
#ifndef STONECOLD_SCENES_SCENE_H
#define STONECOLD_SCENES_SCENE_H

#include <queue>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "Enums.hpp"
#include "SceneAction.hpp"
#include "AssetManager.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::Scenes {

using namespace StoneCold::ECS;
using namespace StoneCold::Common;
using namespace StoneCold::Assets;

//
// This is the central Scene class
// - Responsible for running a ECS with Scene specific systems
// - Manages Entities and reacts to any Update/Render call from the main loop
// - Handles (Input) Actions created by the main Game class
// 
class Scene  {
public:
	Scene(scUint32 maxEntities, AssetManager& assetManager, sf::RenderWindow* renderWindow) 
		: _ecs(EntityComponentSystem(maxEntities))
		, _assetManager(assetManager)
		, _renderWindow(renderWindow)
		, _pendingActions(std::vector<SceneAction>())
		, _sceneEventCallback(nullptr) 
		, _camera(renderWindow->getDefaultView())
		{ }

	inline EntityComponentSystem* GetECS() { return &_ecs; }

	virtual bool Initialize() = 0;

	virtual void Start() = 0;
	virtual void Stop() = 0;
	inline bool IsActive() const { return _isActive; }

	virtual bool HandleEvent(const sf::Event&) = 0;
	virtual void HandleInput(sf::WindowBase*) = 0;
	virtual void Update(scUint32) = 0;
	virtual void Render() = 0;

	inline void ClearActions() { _pendingActions.clear(); }
	inline void RegisterAction(SceneAction&& action) { _pendingActions.emplace_back(action); }

	void SetSceneEventCallback(std::function<void(SceneEvent, SceneType)> callback) { _sceneEventCallback = callback; }

protected:
	bool _isActive;
	EntityComponentSystem _ecs;
	AssetManager& _assetManager;
	sf::RenderWindow* _renderWindow;
	std::vector<SceneAction> _pendingActions;
	std::function<void(SceneEvent, SceneType)> _sceneEventCallback;
	// Camera of the current scene
	sf::View _camera; 
};

}

#endif
