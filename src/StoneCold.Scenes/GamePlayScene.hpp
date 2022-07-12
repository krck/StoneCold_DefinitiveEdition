
#ifndef STONECOLD_SCENES_GAMEPLAYSCENE_H
#define STONECOLD_SCENES_GAMEPLAYSCENE_H

#include "Types.hpp"
#include "Scene.hpp"
#include "MapManager.hpp"
#include "MapTileHelper.hpp"
#include "SystemInput.hpp"
#include "SystemAnimation.hpp"
#include "SystemInputAnimation.hpp"
#include "SystemInputTransform.hpp"
#include "SystemMotionRender.hpp"
#include "SystemStaticRender.hpp"

namespace StoneCold::Scenes {

using namespace StoneCold::ECS;
using namespace StoneCold::Core;
using namespace StoneCold::Assets;

class GamePlayScene : public Scene {
public:
	GamePlayScene(scUint32 maxEntities, AssetManager& assetManager);
	GamePlayScene(const GamePlayScene&) = delete;
	GamePlayScene& operator=(const GamePlayScene&) = delete;

	virtual bool Initialize() override;

	virtual bool HandleEvent() override;
	virtual void HandleInput() override;
	virtual void Update(scUint32 frameTime) override;
	virtual void Render(sf::RenderTarget* renderTarget, sf::View* camera) override;

	~GamePlayScene() = default;

private:
	void SpawnPlayer();
	void SpawnEnemy();
	void CreateLevelMap(LevelType levelType);

private:
	MapManager _mapManager;
	scSptr<GameMap> _currentMapTiles;
	// EntityId's for fast access
	scEntityId _player;
	// System ptrs for fast access
	scSptr<SystemAnimation> _systemAnimation;
	scSptr<SystemInput> _systemInput;
	scSptr<SystemInputAnimation> _systemInputAnimation;
	scSptr<SystemInputTransform> _systemInputTransform;
	scSptr<SystemMotionRender> _systemMotionRender;
	scSptr<SystemStaticRender> _systemStaticRender;

	sf::Sprite _playerSprite;
};

}

#endif
