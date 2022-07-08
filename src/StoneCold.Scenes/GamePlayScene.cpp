
#include "GamePlayScene.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Scenes;

GamePlayScene::GamePlayScene(scUint32 maxEntities)
	: Scene(maxEntities)
	, _player(0)
	, _systemInput(nullptr)
	, _systemInputTransform(nullptr)
	, _systemMotionRender(nullptr) { }

bool GamePlayScene::Initialize() {
	// Create all Systems needed by the GamePlayScene ECS (keep ptr variables for quick access)
	_systemInput = std::make_shared<SystemInput>(_ecs);
	_systemInputTransform = std::make_shared<SystemInputTransform>(_ecs);
	_systemMotionRender = std::make_shared<SystemMotionRender>(_ecs);

	// Add all the GamePlayScene Systems to the ECS
	_ecs.AddSystem<SystemInput>(_systemInput);
	_ecs.AddSystem<SystemInputTransform>(_systemInputTransform);
	_ecs.AddSystem<SystemMotionRender>(_systemMotionRender);

	SpawnPlayer();
	return true;
}

bool GamePlayScene::HandleEvent() {
	return true;
}

void GamePlayScene::HandleInput() {
	_systemInput->HandleInput();
}

void GamePlayScene::Update(scUint32 frameTime) {
	_systemInputTransform->Update(frameTime);
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

	auto playerPosition = sf::Vector2f(100.f, 100.f);
	auto playerSpeed = 250.f;

	if (!_playerTex.loadFromFile("D:\\Projects\\StoneCold_DefinitiveEdition\\build\\Debug\\x64\\bin\\assets\\player\\Dwarf_Sprite.png"))
	{
		// error...
	}
	//texture.setSmooth(true);
	_playerSprite.setTexture(_playerTex);
	_playerSprite.scale(sf::Vector2f(5.f, 5.f)); 
	_playerSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));

	_player = _ecs.CreateEntity();
	_ecs.AddComponent<CInput>(_player, {});
	_ecs.AddComponent<CTransform>(_player, { playerPosition, sf::Vector2f(), playerSpeed, 0.f, 0.f });
	_ecs.AddComponent<CSprite>(_player, { _playerTex, _playerSprite, sf::Color::White });
 
}


void GamePlayScene::SpawnEnemy() {

}
