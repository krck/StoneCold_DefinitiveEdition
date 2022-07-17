
#include "MainMenuScene.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Scenes;
using namespace StoneCold::Assets;
using namespace StoneCold::GUI;

MainMenuScene::MainMenuScene(scUint32 maxEntities, AssetManager& assetManager) 
	: Scene(maxEntities, assetManager) 
	, _guiWidgets(std::vector<scSptr<Widget>>())
	{ }

bool MainMenuScene::Initialize() {
	CreateGui();
	return true;
} 

bool MainMenuScene::HandleEvent(const sf::Event&) {
	return true;  
}

void MainMenuScene::HandleInput(sf::WindowBase* window) {
	for (const auto& widget : _guiWidgets) {
		for (const auto& action : _pendingActions) {
			// Update on mouse movement
			if(action.GetAction() == "ACTN_CURSOR_MOVE") 
				widget->OnMouseMoved(sf::Mouse::getPosition(*window));

			// Trigger left mouse press/release
			if(action.GetAction() == "ACTN_ACTION_PRIMARY" && action.GetType() == ActionType::Start)
				widget->OnMousePressed();
			else if (action.GetAction() == "ACTN_ACTION_PRIMARY" && action.GetType() == ActionType::End)
				widget->OnMouseReleased();	
		}
	}
}

void MainMenuScene::Update(scUint32) {

}

void MainMenuScene::Render(sf::RenderTarget* renderTarget, sf::View*) {
	renderTarget->setView(renderTarget->getDefaultView());
	for (const auto& widget : _guiWidgets) {
		widget->Render(renderTarget);
	}
}

void MainMenuScene::CreateGui() {
	// Load the main font
	const auto& buttonFont = _assetManager.GetFont("Font_Crom");

	// Add "PLAY" Button
	_assetManager.AddSpriteStatic("MainMenuButton_Play", "Sprite_GuiButton");
	auto buttonPlaySprite = _assetManager.GetSpriteStatic("MainMenuButton_Play");
	auto buttonPlay = std::make_shared<Button>(buttonPlaySprite->GetSprite(), buttonFont, 48, "PLAY");
	buttonPlay->SetPosition(sf::Vector2f(800.f, 600.f));
	buttonPlay->SetScale(sf::Vector2f(2.f, 2.f));
	buttonPlay->SetCallback(std::bind(&MainMenuScene::OnPlayClicked, this));
	_guiWidgets.push_back(buttonPlay);

	// Add "OPTIONS" Button
	_assetManager.AddSpriteStatic("MainMenuButton_Options", "Sprite_GuiButton");
	auto buttonOptionsSprite = _assetManager.GetSpriteStatic("MainMenuButton_Options");
	auto buttonOptions = std::make_shared<Button>(buttonOptionsSprite->GetSprite(), buttonFont, 48, "OPTIONS");
	buttonOptions->SetPosition(sf::Vector2f(800.f, 730.f));
	buttonOptions->SetScale(sf::Vector2f(2.f, 2.f));
	buttonOptions->SetCallback(std::bind(&MainMenuScene::OnOptionsClicked, this));
	_guiWidgets.push_back(buttonOptions);

	// Add "QUIT" Button
	_assetManager.AddSpriteStatic("MainMenuButton_Quit", "Sprite_GuiButton");
	auto buttonQuitSprite = _assetManager.GetSpriteStatic("MainMenuButton_Quit");
	auto buttonQuit = std::make_shared<Button>(buttonQuitSprite->GetSprite(), buttonFont, 48, "QUIT");
	buttonQuit->SetPosition(sf::Vector2f(800.f, 860.f));
	buttonQuit->SetScale(sf::Vector2f(2.f, 2.f));
	buttonQuit->SetCallback(std::bind(&MainMenuScene::OnQuitClicked, this));
	_guiWidgets.push_back(buttonQuit);
}

void MainMenuScene::OnPlayClicked() {
	if(_sceneEventCallback != nullptr)
		_sceneEventCallback(SceneEvent::ChangeScene, SceneType::GamePlay);
}

void MainMenuScene::OnOptionsClicked() {
	//std::cout <<"Options Callback!" <<std::endl;
}

void MainMenuScene::OnQuitClicked() {
	if(_sceneEventCallback != nullptr)
		_sceneEventCallback(SceneEvent::QuitGame, SceneType::None);
}
