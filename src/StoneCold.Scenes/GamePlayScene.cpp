
#include "GamePlayScene.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Scenes;
using namespace StoneCold::Assets;

GamePlayScene::GamePlayScene(scUint32 maxEntities, AssetManager& assetManager, sf::RenderWindow* renderWindow)
	: Scene(maxEntities, assetManager, renderWindow)
	, _showDebugOutput(false)
	, _mapManager(MapManager())
	, _currentMapTiles(nullptr)
	, _systemAnimation(std::make_shared<SystemAnimation>(_ecs))
	, _systemCollisionDetection(std::make_shared<SystemCollisionDetection>(_ecs))
	, _systemCollisionResolution(std::make_shared<SystemCollisionResolution>(_ecs))
	, _systemInput(std::make_shared<SystemInput>(_ecs))
	, _systemInputAnimation(std::make_shared<SystemInputAnimation>(_ecs))
	, _systemInputTransform(std::make_shared<SystemInputTransform>(_ecs))
	, _systemMotionRender(std::make_shared<SystemMotionRender>(_ecs))
	, _systemStaticRender(std::make_shared<SystemStaticRender>(_ecs))
	, _player(0)
	{ }

bool GamePlayScene::Initialize() {
	// Add all the GamePlayScene Systems to the ECS
	_ecs.AddSystem<SystemAnimation>(_systemAnimation);
	_ecs.AddSystem<SystemCollisionDetection>(_systemCollisionDetection);
	_ecs.AddSystem<SystemCollisionResolution>(_systemCollisionResolution);
	_ecs.AddSystem<SystemInput>(_systemInput);
	_ecs.AddSystem<SystemInputAnimation>(_systemInputAnimation);
	_ecs.AddSystem<SystemInputTransform>(_systemInputTransform);
	_ecs.AddSystem<SystemMotionRender>(_systemMotionRender);
	_ecs.AddSystem<SystemStaticRender>(_systemStaticRender);

	_camera = sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(_renderWindow->getSize())));

	CreateLevelMap(LevelType::Grassland);
	SpawnEnemy();
	SpawnPlayer();
	return true;
}

void GamePlayScene::Start() {
	_isActive = true;

	// Re-calculate the current Camera View, when coming from any other scene
	const auto& playerSpriteComp = _ecs.GetComponentArray<CSprite>()->at(_player);
	_camera = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(_renderWindow->getSize()));
	_camera.setCenter(playerSpriteComp.Sprite->getPosition());
	_renderWindow->setView(_camera);
}

void GamePlayScene::Stop() {
	_isActive = false;
}

bool GamePlayScene::HandleEvent(const sf::Event& event) {
	if (event.type == sf::Event::Resized) { 
		// Update the view to the new size of the window
		const auto& playerSpriteComp = _ecs.GetComponentArray<CSprite>()->at(_player);
		_camera = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(event.size.width, event.size.height));
		_camera.setCenter(playerSpriteComp.Sprite->getPosition());
		_renderWindow->setView(_camera);
	}
	return true;
}

void GamePlayScene::HandleInput(sf::WindowBase*) {
	_systemInput->HandleInput(_pendingActions);
	_systemInputAnimation->HandleInput(_pendingActions);

	// ESC to go back to the Main Menu
	for (const auto& action : _pendingActions) {
		if(action.GetAction() == "ACTN_ESC" && _sceneEventCallback != nullptr)
			_sceneEventCallback(SceneEvent::ChangeScene, SceneType::MainMenu);
		else if(action.GetAction() == "DEBUG_MODE" && action.GetType() == ActionType::Start)
			_showDebugOutput = !_showDebugOutput;
		// else if(action.GetAction() == "DEBUG_MODE" && action.GetType() == ActionType::End)
		// 	_showDebugOutput = false;
	}
	
	ClearActions();
}
 
void GamePlayScene::Update(scUint32 frameTime) {
	_systemInputTransform->Update(frameTime);
	_systemAnimation->Update(frameTime);
	
	//_systemCollisionDetection->Update(frameTime);
	//_systemCollisionResolution->Update(frameTime);
}

void GamePlayScene::Render() {
	scUint32 drawCount = 0;
	// First: Render all static sprites (MapTiles)
	drawCount += _systemStaticRender->Render(_renderWindow, _camera);
	// Second: Render all moving sprites (Player, NPCs, ...)
	drawCount += _systemMotionRender->Render(_renderWindow, _camera);
	// Third: Render the GUI (always top Layer)
	// ...

	// Debug "output" with BoundingBox rectangles
	if(_showDebugOutput) {
		drawCount += _systemCollisionDetection->Render(_renderWindow, _camera);
		//std::cout <<"Rendered entities: " <<drawCount <<std::endl;
	}

	// Get the Player Sprite from the ECS and center the camera (View) on the player position
	// (Window view must be set after every change as it is copied into the renderTarget object)
	const auto& playerSpriteComp = _ecs.GetComponentArray<CSprite>()->at(_player);
	_camera.setCenter(playerSpriteComp.Sprite->getPosition());
	_renderWindow->setView((_camera));
}

void GamePlayScene::SpawnPlayer() {
	auto playerSpriteScale = 5.f;
	auto playerPosition = _spawnPoint;
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
	_ecs.AddComponent<CPosition>(_player, { playerPosition, playerPosition });
	_ecs.AddComponent<CTransform>(_player, { sf::Vector2f(), playerSpeed, 0.f, playerSpriteScale });
	_ecs.AddComponent<CSprite>(_player, { playerSprite, sf::IntRect(sf::Vector2i(0, 0), playerSpriteAsset->GetFrameSize()), sf::Color::White, 1.f });
	_ecs.AddComponent<CBoundingBox>(_player, { _player, (sf::Vector2f(14.f, 18.f) * playerSpriteScale), (sf::Vector2f(7.f, 9.f) * playerSpriteScale), sf::Vector2f(), true });
}

void GamePlayScene::SpawnEnemy() {
	auto enemySpriteScale = 5.f;
	auto enemyPosition = sf::Vector2f(800.f, 800.f);

	_assetManager.AddSpriteAnimated("Sprite_Skeleton_1", "Sprite_Skeleton");
	auto skeletonSpriteAsset = _assetManager.GetSpriteAnimated("Sprite_Skeleton_1");
	auto skeletonAnimations = skeletonSpriteAsset->GetAnimations();
	auto defaultAnimation = skeletonSpriteAsset->GetDefaultAnimation();
	auto skeletonSprite = skeletonSpriteAsset->GetSprite();
	skeletonSprite->move(enemyPosition);

	auto enemy = _ecs.CreateEntity();
	_ecs.AddComponent<CAnimation>(enemy, { skeletonAnimations, skeletonSpriteAsset->GetFrameSize(), defaultAnimation, defaultAnimation, 0, 0, 0 });
	_ecs.AddComponent<CPosition>(enemy, { enemyPosition, enemyPosition });
	_ecs.AddComponent<CTransform>(enemy, { sf::Vector2f(), 200.f, 0.f, enemySpriteScale });
	_ecs.AddComponent<CSprite>(enemy, { skeletonSprite, sf::IntRect(sf::Vector2i(0, 0), skeletonSpriteAsset->GetFrameSize()), sf::Color::White, 1.f });
}

void GamePlayScene::CreateLevelMap(LevelType levelType) {

	scUint64 mapSize = 60;
	auto mapTileScale = 6.0f;
	auto textureFrameWidth = 32.0f;

	_currentMapTiles = _mapManager.GenerateMap(levelType, sf::Vector2i(mapSize, mapSize));
	auto tile = _ecs.CreateEntity();

	sf::RenderTexture mapRenderTexture;
	const auto textureSize = (mapSize * mapTileScale * textureFrameWidth);
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

			const auto tileWidth = tileSprite->getLocalBounds().width * mapTileScale;
			const auto tileHeight = tileSprite->getLocalBounds().height * mapTileScale;
			const auto tilePosition = sf::Vector2f(tileWidth * column, tileHeight * row);

			tileSprite->setScale({ mapTileScale, mapTileScale });
			tileSprite->setPosition(tilePosition);
			tileSprite->setTextureRect(mapTileRenderInfo.TileTextureRect);

			mapRenderTexture.draw(*tileSprite.get());

			// Add the CollisionComponent in case its a Wall-Tile
			if(static_cast<int>(_currentMapTiles->TileGrid[row][column]) > static_cast<int>(MapTileType::Floor_Shadow)) {
				auto tileCollision = _ecs.CreateEntity();
				_ecs.AddComponent<CPosition>(tileCollision, { tilePosition, tilePosition });
				_ecs.AddComponent<CBoundingBox>(tileCollision, { tile, sf::Vector2f(tileWidth, tileHeight), sf::Vector2f(tileWidth / 2.f, tileHeight / 2.f), sf::Vector2f(), false });
			}

			if(_currentMapTiles->TileGrid[row][column] == MapTileType::Portal)
				_spawnPoint = tilePosition;
		}
	}
	mapRenderTexture.display();

	auto tmpTex = mapRenderTexture.getTexture();
	_assetManager.AddSpriteStatic("Sprite_Grassland_Generated", std::move(tmpTex), sf::Vector2i(textureSize, textureSize));
	auto fullMapSprite = _assetManager.GetSpriteStatic("Sprite_Grassland_Generated");
	auto renderRect = sf::IntRect(sf::Vector2i(), sf::Vector2i(textureSize, textureSize));

	// Add the Tile to the ECS
	_ecs.AddComponent<CStatic>(tile, { 0.f, 1.f });
	_ecs.AddComponent<CPosition>(tile, { sf::Vector2f(), sf::Vector2f() });
	_ecs.AddComponent<CSprite>(tile, { fullMapSprite->GetSprite(), renderRect, sf::Color::White, 1.f });
}
