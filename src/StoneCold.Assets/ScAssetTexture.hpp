
#ifndef STONECOLD_ASSETS_SCASSETTEXTURE_H
#define STONECOLD_ASSETS_SCASSETTEXTURE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "ScAsset.hpp"

namespace StoneCold::Assets {

using namespace StoneCold::Common;

class ScAssetTexture : public ScAsset {
public:
	ScAssetTexture(const std::string& name, sf::Texture&& texture) : ScAsset(name), _texture(std::move(texture)) {}

	inline const sf::Texture& GetTexture() const { return _texture; }

private:
	sf::Texture _texture;
};

}

#endif
