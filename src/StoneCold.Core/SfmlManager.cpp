
#include "SfmlManager.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Common;

//
// Initializes the SFML Ressources and 
// creats/show the application Window
//
bool SfmlManager::Initialize(const AssetManager& assets) {
	try {
		// Load these Settings via .json input
		const nlohmann::json settings = assets.GetSettingsJson();
		const auto windowName = 	settings["window"]["name"].get<std::string>() ;
		const auto windowWidth = 	settings["window"]["width"].get<int>();
		const auto windowHeight = 	settings["window"]["height"].get<int>();
		const auto vSyncEnabled = 	settings["window"]["vSync"].get<bool>();
		const auto maxFPS = 		settings["window"]["maxFps"].get<int>();
		const auto pixelDepth = 	settings["window"]["pixelDepth"].get<int>();

		// Create the Window and the main View
		auto windowNameFull = (windowName + " - v" + StoneCold_VERSION_MAJOR + "." + StoneCold_VERSION_MINOR);
		_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight), pixelDepth), windowNameFull, sf::Style::Default);
		_window->setActive(true);

		// Set Framerate OR VSync (They do not go well together. Is one or the other)
		// if(!vSyncEnabled) {
		// 	_window->setVerticalSyncEnabled(false);
		// 	_window->setFramerateLimit(maxFPS);
		// } 
		// else {
		// 	_window->setVerticalSyncEnabled(true);
		// }

		return true;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
}
