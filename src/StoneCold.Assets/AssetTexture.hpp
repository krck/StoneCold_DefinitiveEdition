
#ifndef STONECOLD_ASSETS_ASSETTEXTURE_H
#define STONECOLD_ASSETS_ASSETTEXTURE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "Assets.hpp"

namespace StoneCold::Assets {

using namespace StoneCold::Core;

class AssetTexture : public Asset {
public:
	AssetTexture(const std::string& name, sf::Texture&& texture) : Asset(name), _texture(std::move(texture)) {}

	inline const sf::Texture& GetTexture() const { return _texture; }

private:
	sf::Texture _texture;
};

}

#endif
