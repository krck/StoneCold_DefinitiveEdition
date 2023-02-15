
#ifndef STONECOLD_ASSETS_SCASSETFONT_H
#define STONECOLD_ASSETS_SCASSETFONT_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "ScAsset.hpp"

namespace StoneCold::Assets {

using namespace StoneCold::Common;

class ScAssetFont : public ScAsset {
public:
	ScAssetFont(const std::string& name, sf::Font&& font) : ScAsset(name), _font(std::move(font)) {}

	inline const sf::Font& GetFont() const { return _font; }

private:
	sf::Font _font;
};

}

#endif
