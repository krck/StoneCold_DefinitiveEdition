
#ifndef STONECOLD_ECS_COMPONENTS_H
#define STONECOLD_ECS_COMPONENTS_H

#include <map>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "ScAssetSpriteAnimated.hpp"

namespace StoneCold::ECS {

using namespace StoneCold::Common;
using namespace StoneCold::Assets;

struct CInput {
	std::map<std::string, ActionType> Actions = std::map<std::string, ActionType>();
	// Only logic in Components: Simple lookup-helper for Actions map (Check if contains and if its a specific ActionType)
	inline bool ActionStart(const std::string& a) const { return (Actions.find(a) != Actions.end() ? (Actions.at(a) == ActionType::Start) : false); }
	inline bool ActionEnd(const std::string& a) const { return (Actions.find(a) != Actions.end() ? (Actions.at(a) == ActionType::End) : false); }
};

struct CTransform {
	sf::Vector2f PositionAbs;
	sf::Vector2f Velocity;
	float Speed;
	float Angle;
	float Scale;
};

struct CStaticPosition {
	sf::Vector2f PositionAbs;
	float Angle;
	float Scale;
};

struct CSprite {
	scSptr<sf::Sprite> Sprite;
	sf::IntRect TextureRect;
	sf::Color ColorMod;
	float FlipSprite;
};

struct CAnimation {
	scSptr<std::unordered_map<std::string, AssetAnimation>> Animations;
	sf::Vector2i AnimationFrameSize;
	std::string DefaultAnimation;
	std::string CurrentAnimation;
	scUint64 AnimationLockFrame;
	scUint64 CurrentFrame;
	scUint16 CurrentIndex;
};

struct CCollision {
	sf::Vector2f Hitbox;
};

struct CScore {
	scInt32 Score;
};

}

#endif
