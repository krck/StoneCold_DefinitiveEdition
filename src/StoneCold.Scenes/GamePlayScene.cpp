
#include "GamePlayScene.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Scenes;
using namespace StoneCold::Assets;

GamePlayScene::GamePlayScene(scUint32 maxEntities, AssetManager& assetManager, sf::RenderWindow* renderWindow)
	: Scene(maxEntities, assetManager, renderWindow)
	, _showDebugOutput(false)
	, _cameraZoom(1.f)
	, _mapManager(MapManager())
	, _currentMapTiles(nullptr)
	, _ePlayer(0)
	, _eMapBackground(0)
	, _eMapTiles(std::vector<scEntityId>())
	, _eEnemies(std::vector<scEntityId>())
	{ }

bool GamePlayScene::Initialize() {
	_camera = sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(_renderWindow->getSize())));

	CreateLevelMap(LevelType::Grassland);
	SpawnEnemies();
	SpawnPlayer();
	return true;
}

void GamePlayScene::Start() {
	_isActive = true;
	// Re-calculate the current Camera View, when coming from any other scene
	ResizeCamera();
}

void GamePlayScene::Stop() {
	_isActive = false;
}

bool GamePlayScene::HandleEvent(const sf::Event& event) {
	if (event.type == sf::Event::Resized) { 
		// Re-calculate the current Camera View, when window is resized
		ResizeCamera();
	}
	return true;
}

void GamePlayScene::HandleInput(sf::WindowBase*) {
	SystemInputSceneSpecific();
	SystemInputPlayer();
	SystemInputAnimation();
	// After all input was handled, reset the _pendingActions
	ClearActions();
}
 
void GamePlayScene::Update(scUint32 frameTime) {
	SystemUpdateTransformation(frameTime);
	SystemUpdateAnimation(frameTime);
	
	//_systemCollisionDetection->Update(frameTime);
	//_systemCollisionResolution->Update(frameTime);
}

void GamePlayScene::Render() {
	// First: Render all static sprites (MapTiles)
	SystemRenderStaticSprites();
	// Second: Render all moving sprites (Player, NPCs, ...)
	SystemRenderMotionSprites();
	// Third: Render the GUI (always top Layer)
	// ...

	// Debug "output" with BoundingBox rectangles
	if(_showDebugOutput) {
		SystemRenderDebugOutput();
	}

	// Get the Player Sprite from the ECS and center the camera (View) on the player position
	// (Window view must be set after every change as it is copied into the renderTarget object)
	const auto& playerSpriteComp = _ecm.GetComponent<CSprite>(_ePlayer);
	_camera.setCenter(playerSpriteComp.Sprite->getPosition());
	_renderWindow->setView((_camera));
}

void  GamePlayScene::ResizeCamera() {
	const auto& playerSpriteComp = _ecm.GetComponent<CSprite>(_ePlayer);
	_camera = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(_renderWindow->getSize()));
	_camera.setCenter(playerSpriteComp.Sprite->getPosition());
	_camera.zoom(_cameraZoom);
	_renderWindow->setView(_camera);
}

// Input system logic
void GamePlayScene::SystemInputSceneSpecific() {
	for (const auto& action : _pendingActions) {
		// ESC to go back to the Main Menu
		if(action.GetAction() == "ACTN_ESC" && _sceneEventCallback != nullptr) {
			_sceneEventCallback(SceneEvent::ChangeScene, SceneType::MainMenu);
		}
		else if(action.GetAction() == "DEBUG_MODE" && action.GetType() == ActionType::Start) {
			_showDebugOutput = !_showDebugOutput;
		}
		else if(action.GetAction() == "ZOOM_IN" && action.GetType() == ActionType::Start) {
			_cameraZoom = (_cameraZoom <= 1.f ? 1.f : _cameraZoom - 0.1f);
			ResizeCamera();
		}
		else if(action.GetAction() == "ZOOM_OUT" && action.GetType() == ActionType::Start) {
			const float maxZoom = (_showDebugOutput ? 6.f : 1.5f);
			_cameraZoom = (_cameraZoom >= maxZoom ? maxZoom : _cameraZoom + 0.1f);
			ResizeCamera();
		}
	}
}

// Input system logic
void GamePlayScene::SystemInputPlayer() {
	auto& cPlayerInput = _ecm.GetComponent<CInput>(_ePlayer);
	auto& cPlayerAnim = _ecm.GetComponent<CAnimation>(_ePlayer);
		
	// Store all input actions in a simple lookup, by action name
	for (const auto& act : _pendingActions) {
		cPlayerInput.Actions[act.GetAction()] = act.GetType();
	}

	// if(a.AnimationLockFrame >= a.CurrentFrame)
	// 	continue;

	// Check if player is moving
	auto movingX = ((-1.0f * cPlayerInput.ActionStart("ACTN_LEFT")) + cPlayerInput.ActionStart("ACTN_RIGHT"));
	auto movingY = ((-1.0f * cPlayerInput.ActionStart("ACTN_UP")) + cPlayerInput.ActionStart("ACTN_DOWN"));
	if (movingX != 0 || movingY != 0)
		cPlayerAnim.CurrentAnimation = "Walk";
	else //if (movingX == 0 && movingY == 0)
		cPlayerAnim.CurrentAnimation = "Idle";

	cPlayerAnim.AnimationLockFrame = cPlayerAnim.CurrentFrame;

	if (cPlayerInput.ActionStart("ACTN_ACTION_PRIMARY")) {
		cPlayerAnim.CurrentAnimation = "ATK_Light";
		cPlayerAnim.AnimationLockFrame = (cPlayerAnim.CurrentFrame + (*cPlayerAnim.Animations)[cPlayerAnim.CurrentAnimation].FrameCount) + 1;
	}
	if (cPlayerInput.ActionStart("ACTN_ACTION_SECONDARY")) {
		cPlayerAnim.CurrentAnimation = "ATK_Heavy";
		cPlayerAnim.AnimationLockFrame = (cPlayerAnim.CurrentFrame + (*cPlayerAnim.Animations)[cPlayerAnim.CurrentAnimation].FrameCount) + 1;
	}
	if (cPlayerInput.ActionStart("ACTN_ACTION_SPECIAL")) {
		cPlayerAnim.CurrentAnimation = "ATK_Special";
		cPlayerAnim.AnimationLockFrame = (cPlayerAnim.CurrentFrame + (*cPlayerAnim.Animations)[cPlayerAnim.CurrentAnimation].FrameCount) + 1;
	}
}

// Input system logic
void GamePlayScene::SystemInputAnimation() {

}

// Update system logic
void GamePlayScene::SystemUpdateTransformation(scUint32 frameTime) {
	/*
	auto& inputComponents = *_ecs.GetComponentArray<CInput>();
	auto& transformComponents = *_ecs.GetComponentArray<CTransform>();
	auto& positionComponents = *_ecs.GetComponentArray<CPosition>();

	// Add a simple form of numerical integration (Explicit Euler) to speeds at different FPSs
	// (Explicit Euler works well as long as the speeds is constant or the frameTime is low)
	const float deltaSec = frameTime / 1000.0f;

	for (const auto& entityId : _entities) {
		auto& i = inputComponents[entityId];
		auto& t = transformComponents[entityId];
		auto& p = positionComponents[entityId];

		// For each keykeyStates contains a value of 1 if pressed and a value of 0 if not pressed
		// Add negative and positive velocity so the sprite doesn't move if both are pressed at the same time
		sf::Vector2f tmpVelocity;
		tmpVelocity.x = ((-1.0f * i.ActionStart("ACTN_LEFT")) + i.ActionStart("ACTN_RIGHT"));
		tmpVelocity.y = ((-1.0f * i.ActionStart("ACTN_UP")) + i.ActionStart("ACTN_DOWN"));

		// Normalize the velocity in case of diagonal movement
		// FIND SOME WAY TO DO THIS WITHOUT IF TO NOT DISTURB THE CACHE, OUR LORD AND SAVIOR
		if (tmpVelocity.x != 0 || tmpVelocity.y != 0)
			tmpVelocity = tmpVelocity.normalized();

		t.Velocity.x = (tmpVelocity.x * t.Speed) * deltaSec;
		t.Velocity.y = (tmpVelocity.y * t.Speed) * deltaSec;
		p.PositionAbsPrevious = p.PositionAbs;
		p.PositionAbs += t.Velocity;
	}
	*/
}

// Update system logic
void GamePlayScene::SystemUpdateAnimation(scUint32) {
	/*
	auto& spriteComponents = *_ecs.GetComponentArray<CSprite>();
	auto& animationComponents = *_ecs.GetComponentArray<CAnimation>();

	scUint16 aFrame;
	AssetAnimation* currentAnimation;

	for (const auto& entityId : _entities) {
		auto& s = spriteComponents[entityId];
		auto& a = animationComponents[entityId];

		// Increment the global frame count
		a.CurrentFrame++;

		// Get the current Animation ptr and calculate the animation-frame that should be displayed
		// 				CurrentFrame (global frame count)
		// "divided by" FrameSpeed (how many frames should a animation image be displayed?)
		// "modulo" 	FrameCount (how many frames does the current animation have?)
		currentAnimation = &(*a.Animations)[a.CurrentAnimation];
		aFrame = (a.CurrentFrame / currentAnimation->FrameSpeed) % currentAnimation->FrameCount;

		// Update the Sprite Rect that will be rendered, based on the "current Frame" (X-Offset), the "current Animation" (Y-Offset) and the FrameSize
		s.TextureRect = sf::IntRect(sf::Vector2i(aFrame * a.AnimationFrameSize.x, currentAnimation->Y_Offset), a.AnimationFrameSize);
	}
	*/
}

// Update system logic
void GamePlayScene::SystemUpdateCollisionDetection(scUint32) {
	/*
	auto& boundingBoxComponents = *_ecs.GetComponentArray<CBoundingBox>();
	auto& positionComponents = *_ecs.GetComponentArray<CPosition>();

	for (const auto& entityId : _entities) {
		auto& b = boundingBoxComponents[entityId];
		auto& p = positionComponents[entityId];
		b.Overlap = sf::Vector2f();

		for (const auto& checkEntityId : _entities) {
			auto& checkB = boundingBoxComponents[checkEntityId];
			auto& checkP = positionComponents[checkEntityId];

			// Do not compare AABB of the same entity or the same Type (type e.g.: MapTile to MapTile)
			if(entityId == checkEntityId || b.Type == checkB.Type)
				continue;

			const float deltaX = abs(p.PositionAbs.x - checkP.PositionAbs.x);
			const float deltaY = abs(p.PositionAbs.y - checkP.PositionAbs.y);
			const float overlapX = (b.BBSizeHalf.x + checkB.BBSizeHalf.x) - deltaX;
			const float overlapY = (b.BBSizeHalf.y + checkB.BBSizeHalf.y) - deltaY;
			b.Overlap = sf::Vector2f(overlapX, overlapY);
		}
	}
	*/
}

// Update system logic
void GamePlayScene::SystemUpdateCollisionResolution(scUint32) {
	/*
	auto& boundingBoxComponents = *_ecs.GetComponentArray<CBoundingBox>();
	//auto& transformComponents = *_ecs.GetComponentArray<CTransform>();

	for (const auto& entityId : _entities) {
		auto& b = boundingBoxComponents[entityId];
		//auto& t = transformComponents[entityId];

		if(b.Overlap.x > 0 && b.Overlap.y > 0)
			std::cout <<b.Overlap.x <<" - " <<b.Overlap.y <<std::endl;
	}
	*/
}

// Render system logic
void GamePlayScene::SystemRenderStaticSprites() {
	/*
	// Get the camera bounds to draw only Sprites that are in the current view
	const auto& camCenter = _camera.getCenter();
	const auto& camSize = _camera.getSize();
	const auto cameraRect = sf::FloatRect(sf::Vector2f(camCenter.x - (camSize.x / 2.f), camCenter.y - (camSize.y / 2.f)), camSize);

	std::vector<scEntityId> staticSprites;
	staticSprites.reserve(10);
	staticSprites.push_back(_eMapBackground);

	for (const auto& entityId : staticSprites) {
		auto& cSprite = _ecm.GetComponent<CSprite>(entityId);
		// auto& cStatic = _ecm.GetComponent<CStatic>(entityId);
		// auto& cPosition = _ecm.GetComponent<CPosition>(entityId);

		// Draw Sprite if visible, based on the lastet transformation
		if(cameraRect.findIntersection(cSprite.Sprite->getGlobalBounds())) {
			cSprite.Sprite->setTextureRect(cSprite.TextureRect);
			_renderWindow->draw(*cSprite.Sprite);
		}
	}
	*/
}

// Render system logic
void GamePlayScene::SystemRenderMotionSprites() {
	/*
	// Get the camera bounds to draw only Sprites that are in the current view
	const auto& camCenter = _camera.getCenter();
	const auto& camSize = _camera.getSize();
	const auto cameraRect = sf::FloatRect(sf::Vector2f(camCenter.x - (camSize.x / 2.f), camCenter.y - (camSize.y / 2.f)), camSize);

	auto& spriteComponents = *_ecs.GetComponentArray<CSprite>();
	auto& transformComponents = *_ecs.GetComponentArray<CTransform>();

	for (const auto& entityId : _entities) {
		auto& s = spriteComponents[entityId];
		auto& t = transformComponents[entityId];

		// Transform the Sprite
		s.Sprite->setScale(sf::Vector2f(t.Scale, t.Scale));
		s.Sprite->move(t.Velocity);

		// Draw Sprite if visible, based on the lastet transformation
		if(cameraRect.findIntersection(s.Sprite->getGlobalBounds())) {
			// Flip the Sprit, in case of movement direction change (left/rigt)
			// (This is done by simply flipping the "width" part of the current TextureRect)
			s.FlipSprite = (t.Velocity.x == 0 ? s.FlipSprite : (t.Velocity.x < 0 ? -1.f : 1.f));
			s.TextureRect = (s.FlipSprite < 0
							? sf::IntRect(sf::Vector2i(s.TextureRect.left + s.TextureRect.width, s.TextureRect.top), sf::Vector2i(s.TextureRect.width * -1.f, s.TextureRect.height))
							: sf::IntRect(sf::Vector2i(s.TextureRect.left, s.TextureRect.top), sf::Vector2i(s.TextureRect.width, s.TextureRect.height))
			);
			s.Sprite->setTextureRect(s.TextureRect);
			renderTarget->draw(*s.Sprite);
			drawCount++;
		}
	}
	*/
}

// Render system logic
void GamePlayScene::SystemRenderDebugOutput() {
	/*
	auto& boundingBoxComponents = *_ecs.GetComponentArray<CBoundingBox>();
	auto& positionComponents = *_ecs.GetComponentArray<CPosition>();

	// Get the camera bounds to draw only Sprites that are in the current view
	const auto& camCenter = camera.getCenter();
	const auto& camSize = camera.getSize();
	const auto cameraRect = sf::FloatRect(sf::Vector2f(camCenter.x - (camSize.x / 2.f), camCenter.y - (camSize.y / 2.f)), camSize);

	for (const auto& entityId : _entities) {
		auto& b = boundingBoxComponents[entityId];
		auto& p = positionComponents[entityId];

		// Draw Rect if visible, based on the lastet transformation
		sf::RectangleShape rectangle(sf::Vector2f(b.BBSize.x - 3.f, b.BBSize.y - 3.f));
		rectangle.setPosition(p.PositionAbs);
		if(cameraRect.findIntersection(rectangle.getGlobalBounds())) {
			rectangle.setOutlineThickness(3.f);
			rectangle.setOutlineColor(sf::Color::Red);
			rectangle.setFillColor(sf::Color::Transparent);
			renderTarget->draw(rectangle);
			drawCount++;
		}
	}
	*/
}

void GamePlayScene::SpawnPlayer() {
	/*
	auto playerPosition = _spawnPoint;
	auto playerSpeed = 250.f;

	//texture.setSmooth(true);
	_assetManager.AddSpriteAnimated("Sprite_Player_1", "Sprite_Player");
	auto playerSpriteAsset = _assetManager.GetSpriteAnimated("Sprite_Player_1");
	auto playerAnimations = playerSpriteAsset->GetAnimations();
	auto defaultAnimation = playerSpriteAsset->GetDefaultAnimation();
	auto playerSprite = playerSpriteAsset->GetSprite();
	playerSprite->move(playerPosition);

	const auto aabb = (sf::Vector2f(14.f, 18.f) * playerSpriteAsset->GetScale());
	const auto aabbHalf = (sf::Vector2f(7.f, 9.f) * playerSpriteAsset->GetScale());

	_player = _ecs.CreateEntity();
	_ecs.AddComponent<CInput>(_player, {});
	_ecs.AddComponent<CAnimation>(_player, { playerAnimations, playerSpriteAsset->GetFrameSize(), defaultAnimation, defaultAnimation, 0, 0, 0 });
	_ecs.AddComponent<CPosition>(_player, { playerPosition, playerPosition });
	_ecs.AddComponent<CTransform>(_player, { sf::Vector2f(), playerSpeed, 0.f, playerSpriteAsset->GetScale() });
	_ecs.AddComponent<CSprite>(_player, { playerSprite, sf::IntRect(sf::Vector2i(0, 0), playerSpriteAsset->GetFrameSize()), sf::Color::White, 1.f });
	_ecs.AddComponent<CBoundingBox>(_player, { _player, aabb, aabbHalf, sf::Vector2f(), true });
	*/
}

void GamePlayScene::SpawnEnemies() {
	/*
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
	_ecs.AddComponent<CTransform>(enemy, { sf::Vector2f(), 200.f, 0.f, skeletonSpriteAsset->GetScale() });
	_ecs.AddComponent<CSprite>(enemy, { skeletonSprite, sf::IntRect(sf::Vector2i(0, 0), skeletonSpriteAsset->GetFrameSize()), sf::Color::White, 1.f });
	*/
}

void GamePlayScene::CreateLevelMap(LevelType levelType) {
	/*
	scUint64 mapSize = 60;
	auto mapTileScale = 6.0f;
	auto textureFrameWidth = 32.0f;

	// RNG generate a new Tile Map
	_currentMapTiles = _mapManager.GenerateMap(levelType, sf::Vector2i(mapSize, mapSize));
	auto tile = _ecs.CreateEntity();

	// Create a singular Texture, where all the Map Tiles will be drawn to
	// (Then, when rendering the game the wohle map is only one entity ... not 5.000 or even more)
	sf::RenderTexture mapRenderTexture;
	const auto textureSize = (mapSize * mapTileScale * textureFrameWidth);
	const auto textureFrameSize = sf::Vector2u(textureSize, textureSize);
	if (!mapRenderTexture.create(textureFrameSize)) { } // error
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
	_assetManager.AddSpriteStatic("Sprite_Grassland_Generated", std::move(tmpTex), sf::Vector2i(textureSize, textureSize), 1.f);
	auto fullMapSprite = _assetManager.GetSpriteStatic("Sprite_Grassland_Generated");
	auto renderRect = sf::IntRect(sf::Vector2i(), sf::Vector2i(textureSize, textureSize));

	// Add the Tile to the ECS
	_ecs.AddComponent<CStatic>(tile, { 0.f, 1.f });
	_ecs.AddComponent<CPosition>(tile, { sf::Vector2f(), sf::Vector2f() });
	_ecs.AddComponent<CSprite>(tile, { fullMapSprite->GetSprite(), renderRect, sf::Color::White, 1.f });
	*/
}
