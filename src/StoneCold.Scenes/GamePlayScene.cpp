
#include "GamePlayScene.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Scenes;
using namespace StoneCold::Assets;

GamePlayScene::GamePlayScene(scUint32 maxEntities, AssetManager& assetManager)
	: Scene(maxEntities, assetManager)
	, _mapManager(MapManager())
	, _currentMapTiles(nullptr)
	, _player(0)
	, _systemAnimation(std::make_shared<SystemAnimation>(_ecs))
	, _systemInput(std::make_shared<SystemInput>(_ecs))
	, _systemInputAnimation(std::make_shared<SystemInputAnimation>(_ecs))
	, _systemInputTransform(std::make_shared<SystemInputTransform>(_ecs))
	, _systemMotionRender(std::make_shared<SystemMotionRender>(_ecs))
	, _systemStaticRender(std::make_shared<SystemStaticRender>(_ecs)) { }

bool GamePlayScene::Initialize() {
	// Add all the GamePlayScene Systems to the ECS
	_ecs.AddSystem<SystemAnimation>(_systemAnimation);
	_ecs.AddSystem<SystemInput>(_systemInput);
	_ecs.AddSystem<SystemInputAnimation>(_systemInputAnimation);
	_ecs.AddSystem<SystemInputTransform>(_systemInputTransform);
	_ecs.AddSystem<SystemMotionRender>(_systemMotionRender);
	_ecs.AddSystem<SystemStaticRender>(_systemStaticRender);

	SpawnEnemy();
	SpawnPlayer();
	CreateLevelMap(LevelType::Grassland);
	return true;
}

bool GamePlayScene::HandleEvent(const sf::Event&) {
	return true;
}

void GamePlayScene::HandleInput(sf::WindowBase*) {
	_systemInput->HandleInput(_pendingActions);
	_systemInputAnimation->HandleInput(_pendingActions);

	// ESC to go back to the Main Menu
	for (const auto& action : _pendingActions) {
		if(action.GetAction() == "ACTN_ESC" && _sceneEventCallback != nullptr)
			_sceneEventCallback(SceneEvent::ChangeScene, SceneType::MainMenu);
	}
	
	ClearActions();
}
 
void GamePlayScene::Update(scUint32 frameTime) {
	_systemInputTransform->Update(frameTime);
	_systemAnimation->Update(frameTime);
}

void GamePlayScene::Render(sf::RenderTarget* renderTarget, sf::View* camera) {
	// First: Render all static sprites (MapTiles)
	_systemStaticRender->Render(renderTarget, camera);
	// Second: Render all moving sprites (Player, NPCs, ...)
	_systemMotionRender->Render(renderTarget, camera);
	// Third: Render the GUI (always top Layer)
	// ...

	// Get the Player Sprite from the ECS and center the camera (View) on the player position
	const auto& playerSpriteComp = _ecs.GetComponentArray<CSprite>()->at(_player);
	camera->setCenter(playerSpriteComp.Sprite->getPosition());
	renderTarget->setView((*camera));
}

void GamePlayScene::SpawnPlayer() {
	auto playerSpriteScale = 5.f;
	auto playerSpriteTexRect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32));
	auto playerPosition = sf::Vector2f(100.f, 100.f);
	auto playerSpeed = 250.f;

	//texture.setSmooth(true);
	_assetManager.AddSpriteAnimated("Sprite_Player_1", "Sprite_Player");
	auto playerSpriteAsset = _assetManager.GetSpriteAnimated("Sprite_Player_1");
	auto playerAnimations = playerSpriteAsset->GetAnimations();
	auto defaultAnimation = playerSpriteAsset->GetDefaultAnimation();
	auto playerSprite = playerSpriteAsset->GetSprite();
	playerSprite->move(playerPosition);

	_player = _ecs.CreateEntity();
	_ecs.AddComponent<CInput>(_player, {});
	_ecs.AddComponent<CAnimation>(_player, { playerAnimations, playerSpriteAsset->GetFrameSize(), defaultAnimation, defaultAnimation, 0, 0, 0 });
	_ecs.AddComponent<CTransform>(_player, { playerPosition, sf::Vector2f(), playerSpeed, 0.f, playerSpriteScale });
	_ecs.AddComponent<CSprite>(_player, { playerSprite, playerSpriteTexRect, sf::Color::White, 1.f });

}

void GamePlayScene::SpawnEnemy() {
	auto enemySpriteScale = 5.f;
	auto enemySpriteTexRect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32));
	auto enemyPosition = sf::Vector2f(800.f, 800.f);

	_assetManager.AddSpriteAnimated("Sprite_Skeleton_1", "Sprite_Skeleton");
	auto skeletonSpriteAsset = _assetManager.GetSpriteAnimated("Sprite_Skeleton_1");
	auto skeletonAnimations = skeletonSpriteAsset->GetAnimations();
	auto defaultAnimation = skeletonSpriteAsset->GetDefaultAnimation();
	auto skeletonSprite = skeletonSpriteAsset->GetSprite();
	skeletonSprite->move(enemyPosition);

	auto enemy = _ecs.CreateEntity();
	_ecs.AddComponent<CAnimation>(enemy, { skeletonAnimations, skeletonSpriteAsset->GetFrameSize(), defaultAnimation, defaultAnimation, 0, 0, 0 });
	_ecs.AddComponent<CTransform>(enemy, { enemyPosition, sf::Vector2f(), 200.f, 0.f, enemySpriteScale });
	_ecs.AddComponent<CSprite>(enemy, { skeletonSprite, enemySpriteTexRect, sf::Color::White, 1.f });
}

void GamePlayScene::CreateLevelMap(LevelType levelType) {

	scUint64 mapSize = 60;
	auto mapTileScale = 6.0f;
	auto frameWidth = 32.0f;

	_currentMapTiles = _mapManager.GenerateMap(levelType, sf::Vector2i(mapSize, mapSize));


	sf::RenderTexture mapRenderTexture;
	const auto textureSize = (mapSize * mapTileScale * frameWidth);
	const auto textureFrameSize = sf::Vector2u(textureSize, textureSize);
	if (!mapRenderTexture.create(textureFrameSize)) { /* error... */ }

	mapRenderTexture.clear();
	for (scUint64 row = 0; row < mapSize; row++) {
		for (scUint64 column = 0; column < mapSize; column++) {
			// Get the Tile infos from the generated Map
			const auto& mapTileRenderInfo = MapTileRenderInfos.at(_currentMapTiles->TileGrid[row][column]);
			const auto spriteName = ("Sprite_Grassland_" + mapTileRenderInfo.TileTypeStr);

			_assetManager.AddSpriteStatic(spriteName, "Sprite_Grassland");
			auto tileSpriteAsset = _assetManager.GetSpriteStatic(spriteName);
			auto tileSprite = tileSpriteAsset->GetSprite();

			const auto xPosition = tileSprite->getLocalBounds().width * column * mapTileScale;
			const auto yPosition = tileSprite->getLocalBounds().height * row * mapTileScale;
			const auto tilePosition = sf::Vector2f(xPosition, yPosition);

			tileSprite->setScale({ (mapTileRenderInfo.TileTextureFlip * mapTileScale), (1.f * mapTileScale) });
			tileSprite->setPosition(tilePosition);
			tileSprite->setTextureRect(mapTileRenderInfo.TileTextureRect);

			mapRenderTexture.draw(*tileSprite.get());

			// // Add the CollisionComponent in case its a Wall-Tile
			// if (static_cast<int>(type->first) > static_cast<int>(MapTileType::Floor_Shadow))
			// 	gameECS->AddComponent<CollisionComponent>(entityId, { 2, Vec2(pos.DestRect.w, pos.DestRect.h), pos.DestRect, nullptr });
			// else
			// 	gameECS->RemoveComponent<CollisionComponent>(entityId);
		}
	}
	mapRenderTexture.display();

	auto tmpTex = mapRenderTexture.getTexture();
	_assetManager.AddSpriteStatic("Sprite_Grassland_Generated", std::move(tmpTex), sf::Vector2i(textureSize, textureSize));
	auto fullMapSprite = _assetManager.GetSpriteStatic("Sprite_Grassland_Generated");
	auto renderRect = sf::IntRect(sf::Vector2i(), sf::Vector2i(textureSize, textureSize));

	// Add the Tile to the ECS
	auto tile = _ecs.CreateEntity();
	_ecs.AddComponent<CStaticPosition>(tile, { sf::Vector2f(), 0.f, 1.f });
	_ecs.AddComponent<CSprite>(tile, { fullMapSprite->GetSprite(), renderRect, sf::Color::White, 1.f });
}
