
#ifndef STONECOLD_SCENES_GAMEPLAYSCENE_H
#define STONECOLD_SCENES_GAMEPLAYSCENE_H

#include "Types.hpp"
#include "Scene.hpp"
#include "SystemInput.hpp"
#include "SystemInputTransform.hpp"
#include "SystemMotionRender.hpp"

namespace StoneCold::Scenes {

using namespace StoneCold::Core;
using namespace StoneCold::ECS;

class GamePlayScene : public Scene {
public:
	GamePlayScene(scUint32 maxEntities);
	GamePlayScene(const GamePlayScene&) = delete;
	GamePlayScene& operator=(const GamePlayScene&) = delete;

	virtual bool Initialize() override;

	virtual bool HandleEvent() override;
	virtual void HandleInput() override;
	virtual void Update(scUint32 frameTime) override;
	virtual void Render(sf::RenderTarget* renderTarget) override;

	~GamePlayScene() = default;

private:
	void SpawnPlayer();
	void SpawnEnemy();

private:
	// EntityId's for fast access
	scEntityId _player;
	// System ptrs for fast access
	std::shared_ptr<SystemInput> _systemInput;
	std::shared_ptr<SystemInputTransform> _systemInputTransform;
	std::shared_ptr<SystemMotionRender> _systemMotionRender;

	sf::Texture _playerTex;
	sf::Sprite _playerSprite;
};

}

#endif
