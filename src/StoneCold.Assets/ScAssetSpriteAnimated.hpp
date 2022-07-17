
#ifndef STONECOLD_ASSETS_SCASSETSPRITEANIMATED_H
#define STONECOLD_ASSETS_SCASSETSPRITEANIMATED_H

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "ScAsset.hpp"

namespace StoneCold::Assets {

using namespace StoneCold::Core;

//
// Simple Sturct to hold the singular Animation data (idle, walk, attack, dead, etc.)
//
struct AssetAnimation {
    std::string Name;
    scUint16 FrameSpeed;
    scUint16 FrameCount;
    scUint16 Y_Offset;
};

//
// Sprite Asset with 2D Sprite and all the Animation information
//
class ScAssetSpriteAnimated : public ScAsset {
public:
    ScAssetSpriteAnimated(const std::string& name, const sf::Texture& texture, const std::vector<AssetAnimation>& animations, 
                          const std::string& defaultAnimation, const sf::Vector2i& frameSize) 
                        : ScAsset(name), _frameSize(frameSize), _defaultAnimation(defaultAnimation) {
        // Create and configure the 2D Sprite
        _sprite = std::make_shared<sf::Sprite>();
        _sprite->setTexture(texture);
        _sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), _frameSize));
        // Set every Sprite "Origin" to the Center of the Rect
        _sprite->setOrigin({ _sprite->getLocalBounds().width / 2.f, _sprite->getLocalBounds().height / 2.f });

        // Transform the AssetAnimation data into a lookup map, by name
        std::unordered_map<std::string, AssetAnimation> animationMap;
        for (const auto& a : animations)
            animationMap.insert({ a.Name, a });

        _animations = std::make_shared<std::unordered_map<std::string, AssetAnimation>>(animationMap);
    }

    // Hand out Sprite as shared_ptr for ease of use
    inline scSptr<sf::Sprite> GetSprite() { return _sprite; }
    inline sf::Vector2i GetFrameSize() const { return _frameSize; }

    inline scSptr<std::unordered_map<std::string, AssetAnimation>> GetAnimations() const { return _animations; }
    inline std::string GetDefaultAnimation() const { return _defaultAnimation; }

private:
    scSptr<sf::Sprite> _sprite;
    const sf::Vector2i _frameSize;
    // Animation data
    scSptr<std::unordered_map<std::string, AssetAnimation>> _animations;
    const std::string _defaultAnimation;
};

}

#endif
