
#ifndef STONECOLD_SCENES_GAMEPLAYSCENE_H
#define STONECOLD_SCENES_GAMEPLAYSCENE_H

#include "Types.hpp"
#include "Scene.hpp"
#include "MapManager.hpp"
#include "MapTileHelper.hpp"

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
	void ResizeCamera();

	// Input system logic
	void SystemInputSceneSpecific();
	void SystemInputPlayer();
	void SystemInputAnimation();
	// Update system logic
	void SystemUpdateTransformation(scUint32 frameTime);
	void SystemUpdateAnimation(scUint32 frameTime);
	void SystemUpdateCollisionDetection(scUint32 frameTime);
	void SystemUpdateCollisionResolution(scUint32 frameTime);
	// Render system logic
	void SystemRenderStaticSprites();
	void SystemRenderMotionSprites();
	void SystemRenderDebugOutput();

	void SpawnPlayer();
	void SpawnEnemies();
	void CreateLevelMap(LevelType levelType);

private:
	bool _showDebugOutput;
	float _cameraZoom;
	MapManager _mapManager;
	sf::Vector2f _spawnPoint;
	scSptr<GameMap> _currentMapTiles;
	// EntityId's for fast access
	scEntityId _ePlayer;
	scEntityId _eMapBackground;
	std::vector<scEntityId> _eMapTiles;
	std::vector<scEntityId> _eEnemies;
};

}

#endif
