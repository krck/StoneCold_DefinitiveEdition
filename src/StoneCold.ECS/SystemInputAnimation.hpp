
#ifndef STONECOLD_ECS_SYSTEMINPUTANIMATION_H
#define STONECOLD_ECS_SYSTEMINPUTANIMATION_H

#include "System.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::ECS {

class SystemInputAnimation : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a Transformation and Velocity component will be updated with this System
	//
	SystemInputAnimation(EntityComponentSystem& ecs)
		: System((GetComponentMask<CInput>() | GetComponentMask<CAnimation>()))
		, _ecs(ecs) { }

	SystemInputAnimation(const SystemInputAnimation&) = delete;
	SystemInputAnimation& operator=(const SystemInputAnimation&) = delete;

	virtual void HandleInput() override {
		auto& inputComponents = *_ecs.GetComponentArray<CInput>();
		auto& animationComponents = *_ecs.GetComponentArray<CAnimation>();

		for (const auto& entityId : _entities) {
			auto& i = inputComponents[entityId];
			auto& a = animationComponents[entityId];

			// if(a.AnimationLockFrame >= a.CurrentFrame)
			// 	continue;

			// Check if player is moving
			auto movingX = ((-1.0f * i.KeyStates[sf::Keyboard::A]) + i.KeyStates[sf::Keyboard::D]);
			auto movingY = ((-1.0f * i.KeyStates[sf::Keyboard::W]) + i.KeyStates[sf::Keyboard::S]);
			if (movingX != 0 || movingY != 0)
				a.CurrentAnimation = "Walk";
			else //if (movingX == 0 && movingY == 0)
				a.CurrentAnimation = "Idle";

			a.AnimationLockFrame = a.CurrentFrame;

			if (i.KeyStates[sf::Keyboard::Num1]) {
				a.CurrentAnimation = "ATK_Light";
				a.AnimationLockFrame = (a.CurrentFrame + (*a.Animations)[a.CurrentAnimation].FrameCount) + 1;
			}
			if (i.KeyStates[sf::Keyboard::Num2]) {
				a.CurrentAnimation = "ATK_Heavy";
				a.AnimationLockFrame = (a.CurrentFrame + (*a.Animations)[a.CurrentAnimation].FrameCount) + 1;
			}
			if (i.KeyStates[sf::Keyboard::Num3]) {
				a.CurrentAnimation = "ATK_Special";
				a.AnimationLockFrame = (a.CurrentFrame + (*a.Animations)[a.CurrentAnimation].FrameCount) + 1;
			}
		}
	}

private:
	EntityComponentSystem& _ecs;
};

}

#endif
