
#include "SfmlManager.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Resources;

//
// Initializes the SDL Ressources and 
// creats/show the application Window
//
bool SfmlManager::Initialize(const SettingsManager& settings) {
	try {
		// Load these Settings via .json input
		auto windowName = settings.Get("window", "window_name");
		auto windowWidth = settings.GetInt("window", "window_width");
		auto windowHeight = settings.GetInt("window", "window_height");
		auto windowStyle = (settings.Get("window", "window_style") == "Resize" ? sf::Style::Resize : sf::Style::Default);
		auto vSyncEnabled = settings.GetBool("window", "window_vsync");
		auto maxFPS = settings.GetInt("window", "window_max_fps");
		auto pixelDepth = settings.GetInt("window", "window_pixel_depth");

		// Create the Window
		_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight), pixelDepth), windowName, windowStyle);
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
