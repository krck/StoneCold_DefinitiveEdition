
#ifndef STONECOLD_ASSETS_SCASSETSPRITESTATIC_H
#define STONECOLD_ASSETS_SCASSETSPRITESTATIC_H

#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "ScAsset.hpp"

namespace StoneCold::Assets {

using namespace StoneCold::Common;

class ScAssetSpriteStatic : public ScAsset {
public:
    ScAssetSpriteStatic(const std::string& name, const sf::Texture& texture, const sf::Vector2i& frameSize) : ScAsset(name), _frameSize(frameSize) {
        // Create and configure the 2D Sprite
        _sprite = std::make_shared<sf::Sprite>();
        _sprite->setTexture(texture);
        _sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), _frameSize));
    }

    // Hand out Sprite as shared_ptr for ease of use
    inline scSptr<sf::Sprite> GetSprite() { return _sprite; }
    inline sf::Vector2i GetFrameSize() const { return _frameSize; }

private:
    scSptr<sf::Sprite> _sprite;
    const sf::Vector2i _frameSize;
};

}

#endif
