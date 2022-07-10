
#ifndef STONECOLD_CORE_SFMLMANAGER_H
#define STONECOLD_CORE_SFMLMANAGER_H

#include <string>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "Exception.hpp"
#include "AssetManager.hpp"

namespace StoneCold::Core {

using namespace StoneCold::Assets;

class SfmlManager {
public:
	SfmlManager() {}
	SfmlManager(const SfmlManager&) = delete;
	SfmlManager& operator=(const SfmlManager&) = delete;

	bool Initialize(const AssetManager& assets);
	inline sf::RenderWindow* GetWindow() { return _window.get(); }

	~SfmlManager() = default;

private:
	std::unique_ptr<sf::RenderWindow> _window;
};

}

#endif
