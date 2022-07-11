
#include "GamePlayScene.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Scenes;
using namespace StoneCold::Assets;

GamePlayScene::GamePlayScene(scUint32 maxEntities, AssetManager& assetManager)
	: Scene(maxEntities, assetManager)
	, _mapManager(MapManager())
	, _currentMapTiles(nullptr)
	, _player(0)
	, _systemAnimation(nullptr)
	, _systemInput(nullptr)
	, _systemInputAnimation(nullptr)
	, _systemInputTransform(nullptr)
	, _systemMotionRender(nullptr) { }

bool GamePlayScene::Initialize() {
	// Create all Systems needed by the GamePlayScene ECS (keep ptr variables for quick access)
	_systemAnimation = std::make_shared<SystemAnimation>(_ecs);
	_systemInput = std::make_shared<SystemInput>(_ecs);
	_systemInputAnimation = std::make_shared<SystemInputAnimation>(_ecs);
	_systemInputTransform = std::make_shared<SystemInputTransform>(_ecs);
	_systemMotionRender = std::make_shared<SystemMotionRender>(_ecs);

	// Add all the GamePlayScene Systems to the ECS
	_ecs.AddSystem<SystemAnimation>(_systemAnimation);
	_ecs.AddSystem<SystemInput>(_systemInput);
	_ecs.AddSystem<SystemInputAnimation>(_systemInputAnimation);
	_ecs.AddSystem<SystemInputTransform>(_systemInputTransform);
	_ecs.AddSystem<SystemMotionRender>(_systemMotionRender);

	SpawnEnemy();
	SpawnPlayer();
	CreateLevelMap(LevelType::Grassland);
	return true;
}

bool GamePlayScene::HandleEvent() {
	return true;
}

void GamePlayScene::HandleInput() {
	_systemInput->HandleInput();
	_systemInputAnimation->HandleInput();
}

void GamePlayScene::Update(scUint32 frameTime) {
	_systemInputTransform->Update(frameTime);
	_systemAnimation->Update(frameTime);
}

void GamePlayScene::Render(sf::RenderTarget* renderTarget) {
	// First: Render all static sprites (MapTiles)
	//_staticRenderSystem->Render(_camera);
	// Second: Render all moving sprites (Player, NPCs, ...)
	_systemMotionRender->Render(renderTarget);
	// Third: Render the GUI (always top Layer)
	// ...
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

	scSptr<std::map<std::string, AssetAnimation>> Animations;
	sf::Vector2i AnimationFrameSize;
	std::string CurrentAnimation;
	scUint16 CurrentIndex;

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
	// Pre-defined map patterns
	std::pair<float, float> pattern = { 0.f, 0.f };
	const std::vector<std::pair<float, float>> mapPatterns = {
		{ 0.6f, 0.01f }, // 1) ROCKY: Map with few open spaces, very jagged edges and lots of corridors and obstacles
		{ 0.75f, 0.1f }, // 2) MIXED: Map with bigger open spaces, some jagged edges and few obstacles
		{ 0.95f, 0.2f }	 // 3) FLAT: Map with one massive, open space, smoothe-ish edges and no corridors/obstacles
	};
	// Grassland and Arctic can be FLAT or MIXED, Highlands or Desert can be ROCKY or MIXED, Castle can only be ROCKY
	if (levelType == LevelType::Grassland || levelType == LevelType::Arctic) { pattern = mapPatterns[(rand() & 1) + 1]; }
	else if (levelType == LevelType::Highlands || levelType == LevelType::Desert) { pattern = mapPatterns[(rand() & 1)]; }
	else { pattern = mapPatterns[0]; }

	scUint64 mapSize = 60;
	//auto mapTileScale = 5.f;

	_currentMapTiles = _mapManager.GenerateMap(sf::Vector2i(60, 60), pattern.first, pattern.second);


	for (scUint64 row = 0; row < mapSize; row++) {
		for (scUint64 column = 0; column < mapSize; column++) {
			// Get the Tile data from the generated Map
			//const auto tileType = MAP_TILE_FRAMES.find(_currentMapTiles->TileGrid[row][column]);
			//const auto textureRect = tileType->second.first;
			//const auto textureFlip = tileType->second.second;

			// Add the Tile to the ECS
			//auto tile = _ecs.CreateEntity();
			//_ecs.AddComponent<CStaticPosition>(tile, { });
			//_ecs.AddComponent<CSprite>(tile, { skeletonSprite, enemySpriteTexRect, sf::Color::White, 1.f });

			// auto enemyPosition = sf::Vector2f(800.f, 800.f);
			// _assetManager.AddSpriteAnimated("Skeleton");
			// auto& skeletonSpriteAsset = _assetManager.GetSpriteAnimated("Skeleton");
			// auto skeletonAnimations = skeletonSpriteAsset.GetAnimations();
			// auto defaultAnimation = skeletonSpriteAsset.GetDefaultAnimation();
			// auto skeletonSprite = skeletonSpriteAsset.GetSprite();
			// skeletonSprite->move(enemyPosition);





			// // Map tile position based on row/column within the mapLayout
			// // Get the Entity and its Components
			// const auto entityId = mapTiles[row * MAP_SIZE + column];
			// auto& pos = _positionComponents[entityId];
			// auto& spr = _spriteComponents[entityId];

			// // Update the Source rectange frame inside the texture (Pixels to take, from the .png)
			// // Update the Destination rectangle with the actual position on screen with scaling (Where to put the Pixels)
			// pos.SrcRect = frame.first;
			// pos.DestRect = { column * 96.f, row * 96.f, static_cast<float>(pos.SrcRect.w * 3), static_cast<float>(pos.SrcRect.h * 3) };
			// // Update the MapTile Texture (and texture flip)
			// spr.Texture = mapTexture->GetTextureSDL();
			// spr.Flip = frame.second;

			// // Add the CollisionComponent in case its a Wall-Tile
			// if (static_cast<int>(type->first) > static_cast<int>(MapTileTypes::Floor_Shadow))
			// 	gameECS->AddComponent<CollisionComponent>(entityId, { 2, Vec2(pos.DestRect.w, pos.DestRect.h), pos.DestRect, nullptr });
			// else
			// 	gameECS->RemoveComponent<CollisionComponent>(entityId);
		}
	}


}