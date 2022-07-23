
#ifndef STONECOLD_SCENES_GAMEPLAYSCENE_H
#define STONECOLD_SCENES_GAMEPLAYSCENE_H

#include "Types.hpp"
#include "Scene.hpp"
#include "MapManager.hpp"
#include "MapTileHelper.hpp"
#include "SystemInput.hpp"
#include "SystemAnimation.hpp"
#include "SystemCollisionDetection.hpp"
#include "SystemCollisionResolution.hpp"
#include "SystemInputAnimation.hpp"
#include "SystemInputTransform.hpp"
#include "SystemMotionRender.hpp"
#include "SystemStaticRender.hpp"

namespace StoneCold::Scenes {

using namespace StoneCold::ECS;
using namespace StoneCold::Core;
using namespace StoneCold::Common;
using namespace StoneCold::Assets;

class GamePlayScene : public Scene {
public:
	GamePlayScene(scUint32 maxEntities, AssetManager& assetManager, sf::RenderWindow* renderWindow);
	GamePlayScene(const GamePlayScene&) = delete;
	GamePlayScene& operator=(const GamePlayScene&) = delete;

	virtual bool Initialize() override;

	virtual void Start() override;
	virtual void Stop() override;

	virtual bool HandleEvent(const sf::Event&) override;
	virtual void HandleInput(sf::WindowBase*) override;
	virtual void Update(scUint32 frameTime) override;
	virtual void Render() override;

	~GamePlayScene() = default;

private:
	void SpawnPlayer();
	void SpawnEnemy();
	void CreateLevelMap(LevelType levelType);

private:
	bool _showDebugOutput;
	MapManager _mapManager;
	scSptr<GameMap> _currentMapTiles;
	sf::Vector2f _spawnPoint;
	// System ptrs for fast access
	scSptr<SystemAnimation> _systemAnimation;
	scSptr<SystemCollisionDetection> _systemCollisionDetection;
	scSptr<SystemCollisionResolution> _systemCollisionResolution;
	scSptr<SystemInput> _systemInput;
	scSptr<SystemInputAnimation> _systemInputAnimation;
	scSptr<SystemInputTransform> _systemInputTransform;
	scSptr<SystemMotionRender> _systemMotionRender;
	scSptr<SystemStaticRender> _systemStaticRender;
	// EntityId's for fast access
	scEntityId _player;
};

}

#endif
