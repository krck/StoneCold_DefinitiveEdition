
#ifndef STONECOLD_ECS_SYSTEMANIMATION_H
#define STONECOLD_ECS_SYSTEMANIMATION_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::ECS {

class SystemAnimation : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a Transformation and Velocity component will be updated with this System
	//
	SystemAnimation(EntityComponentSystem& ecs)
		: System((GetComponentMask<CSprite>() | GetComponentMask<CAnimation>()))
		, _ecs(ecs) { }

	SystemAnimation(const SystemAnimation&) = delete;
	SystemAnimation& operator=(const SystemAnimation&) = delete;

	virtual void Update(scUint64) override {
		auto& spriteComponents = *_ecs.GetComponentArray<CSprite>();
		auto& animationComponents = *_ecs.GetComponentArray<CAnimation>();

		scUint16 aFrame;
		AssetAnimation* currentAnimation;

		for (const auto& entityId : _entities) {
			auto& s = spriteComponents[entityId];
			auto& a = animationComponents[entityId];

			// Increment the global frame count
			a.CurrentFrame++;

			// Get the current Animation ptr and calculate the animation-frame that should be displayed
			// 				CurrentFrame (global frame count)
			// "divided by" FrameSpeed (how many frames should a animation image be displayed?)
			// "modulo" 	FrameCount (how many frames does the current animation have?)
			currentAnimation = &(*a.Animations)[a.CurrentAnimation];
			aFrame = (a.CurrentFrame / currentAnimation->FrameSpeed) % currentAnimation->FrameCount;

			// Update the Sprite Rect that will be rendered, based on the "current Frame" (X-Offset), the "current Animation" (Y-Offset) and the FrameSize
			s.TextureRect = sf::IntRect(sf::Vector2i(aFrame * a.AnimationFrameSize.x, currentAnimation->Y_Offset), a.AnimationFrameSize);
		}
	}

private:
	EntityComponentSystem& _ecs;
};

}

#endif
