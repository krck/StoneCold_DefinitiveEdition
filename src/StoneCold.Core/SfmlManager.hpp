
#ifndef STONECOLD_CORE_SFMLMANAGER_H
#define STONECOLD_CORE_SFMLMANAGER_H

#include <string>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "Exception.hpp"
#include "SettingsManager.hpp"

namespace StoneCold::Core {

using namespace StoneCold::Resources;

class SfmlManager {
public:
	SfmlManager() {}
	SfmlManager(const SfmlManager&) = delete;
	SfmlManager& operator=(const SfmlManager&) = delete;

	bool Initialize(const SettingsManager& settings);
	inline sf::RenderWindow* GetWindow() { return _window.get(); }

	~SfmlManager() = default;

private:
	std::unique_ptr<sf::RenderWindow> _window;
};

}

#endif
