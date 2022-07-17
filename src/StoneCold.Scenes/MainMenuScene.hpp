
#ifndef STONECOLD_SCENES_MAINMENUSCENE_H
#define STONECOLD_SCENES_MAINMENUSCENE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "Scene.hpp"
#include "Button.hpp"

namespace StoneCold::Scenes {

using namespace StoneCold::ECS;
using namespace StoneCold::Core;
using namespace StoneCold::Assets;
using namespace StoneCold::GUI;

class MainMenuScene : public Scene {
public:
	MainMenuScene(scUint32 maxEntities, AssetManager& assetManager);
	MainMenuScene(const MainMenuScene&) = delete;
	MainMenuScene& operator=(const MainMenuScene&) = delete;

	virtual bool Initialize() override;

	virtual bool HandleEvent(const sf::Event&) override;
	virtual void HandleInput(sf::WindowBase* window) override;
	virtual void Update(scUint32 frameTime) override;
	virtual void Render(sf::RenderTarget* renderTarget, sf::View* camera) override;

	~MainMenuScene() = default;

private:
	void CreateGui();

	void OnPlayClicked();
	void OnOptionsClicked();
	void OnQuitClicked();

private:
	std::vector<scSptr<Widget>> _guiWidgets;
};

}

#endif