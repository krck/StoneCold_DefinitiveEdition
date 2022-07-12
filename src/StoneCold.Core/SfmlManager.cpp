
#include "SfmlManager.hpp"

using namespace StoneCold::Core;

//
// Initializes the SDL Ressources and 
// creats/show the application Window
//
bool SfmlManager::Initialize(const AssetManager& assets) {
	try {
		// Load these Settings via .json input
		const nlohmann::json settings = assets.GetSettingsJson();
		auto windowName = 	settings["window"]["name"].get<std::string>();
		auto windowWidth = 	settings["window"]["width"].get<int>();
		auto windowHeight = settings["window"]["height"].get<int>();
		auto windowStyle = (settings["window"]["style"].get<std::string>() == "Resize" ? sf::Style::Resize : sf::Style::Default);
		auto vSyncEnabled = settings["window"]["vSync"].get<bool>();
		auto maxFPS = 		settings["window"]["maxFps"].get<int>();
		auto pixelDepth = 	settings["window"]["pixelDepth"].get<int>();

		// Create the Window and the main View
		_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight), pixelDepth), windowName, windowStyle);
		_playerView = std::make_unique<sf::View>(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f((float)windowWidth, (float)windowHeight)));
		_window->setActive(true);

		// Set Framerate OR VSync (They do not go well together. Is one or the other)
		if(!vSyncEnabled) {
			_window->setVerticalSyncEnabled(false);
			_window->setFramerateLimit(maxFPS);
		} 
		else {
			_window->setVerticalSyncEnabled(true);
		}

		return true;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
}
