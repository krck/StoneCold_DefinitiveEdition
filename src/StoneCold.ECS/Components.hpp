
#ifndef STONECOLD_ECS_COMPONENTS_H
#define STONECOLD_ECS_COMPONENTS_H

#include <map>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "AssetSpriteAnimated.hpp"

namespace StoneCold::ECS {

using namespace StoneCold::Core;
using namespace StoneCold::Assets;

struct CInput {
	bool KeyStates[256];
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


/*
struct AnimationComponent {
	const std::unordered_map<std::string, Animation>* Animations;
	const Animation* CurrentAnimation;
	uint32 CurrentFrameIndex;
	uint32 TimeElapsed;

	inline const Animation* GetAnimation(std::string name) {
		auto anim = &Animations->find(name)->second;
		// Reset the FrameIndex if the requested FrameCount is lower
		if (CurrentFrameIndex > anim->FrameCount)
			CurrentFrameIndex = 0;

		return anim;
	}
};

struct AttributeComponentUI {
	UiElementAttribute UiAttribute;
};

struct SpriteLayeredComponent {
	SDL_Texture* TextureBottom;
	SDL_RendererFlip FlipBottom;
	SDL_Texture* TextureTop;
	SDL_RendererFlip FlipTop;
};

struct VelocityComponent {
	Vec2 Velocity;
};

struct ScreenPositionComponent {
	SDL_Rect SrcRect;
	SDL_FRect DestRect;
};

struct ScreenPositionLayeredComponent {
	SDL_Rect SrcRectBottom;
	SDL_FRect DestRectBottom;
	SDL_Rect SrcRectTop;
	SDL_FRect DestRectTop;
};

struct EnemyStateComponent {
	const std::unordered_map<bitMask32, AiAction>* AiActions;
	bitMask32 AiDecisions;
};

*/

}

#endif
