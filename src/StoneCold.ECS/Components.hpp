
#ifndef STONECOLD_ECS_COMPONENTS_H
#define STONECOLD_ECS_COMPONENTS_H

#include <map>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "Enums.hpp"
#include "ScAssetSpriteAnimated.hpp"

namespace StoneCold::ECS {

using namespace StoneCold::Common;
using namespace StoneCold::Assets;

struct Component { bool Active = false; };

struct CInput : public Component {
	std::map<std::string, ActionType> Actions = std::map<std::string, ActionType>();
	// Only logic in Components: Simple lookup-helper for Actions map (Check if contains and if its a specific ActionType)
	inline bool ActionStart(const std::string& a) { return (Actions.find(a) != Actions.end() ? (Actions.at(a) == ActionType::Start) : false); }
	inline bool ActionEnd(const std::string& a) { return (Actions.find(a) != Actions.end() ? (Actions.at(a) == ActionType::End) : false); }
};

struct CPosition : public Component {
	sf::Vector2f PositionAbs = sf::Vector2f();
	sf::Vector2f PositionAbsPrevious = sf::Vector2f();
};

struct CTransform : public Component {
	sf::Vector2f Velocity = sf::Vector2f();
	float Speed = 0.f;
	float Angle = 0.f;
	float Scale = 0.f;
};

struct CStatic : public Component {
	float Angle = 0.f;
	float Scale = 0.f;
};

struct CSprite : public Component {
	scSptr<sf::Sprite> Sprite = nullptr;
	sf::IntRect TextureRect = sf::IntRect();
	sf::Color ColorMod = sf::Color();
	float FlipSprite = 0.f;
};

struct CAnimation : public Component {
	scSptr<std::unordered_map<std::string, AssetAnimation>> Animations = nullptr;
	sf::Vector2i AnimationFrameSize = sf::Vector2i();
	std::string DefaultAnimation = "";
	std::string CurrentAnimation = "";
	scUint64 AnimationLockFrame = 0;
	scUint64 CurrentFrame = 0;
	scUint16 CurrentIndex = 0;
};

struct CBoundingBox : public Component {
	scUint32 Type = 0;
	sf::Vector2f BBSize = sf::Vector2f();
	sf::Vector2f BBSizeHalf = sf::Vector2f();
	sf::Vector2f Overlap = sf::Vector2f();
	bool CalculateOverlap = false;
};

}

#endif
