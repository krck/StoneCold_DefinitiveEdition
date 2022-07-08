
#ifndef STONECOLD_ECS_SYSTEMTRANSFORM_H
#define STONECOLD_ECS_SYSTEMTRANSFORM_H

#include "System.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::ECS {

class SystemInputTransform : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a Transformation and Velocity component will be updated with this System
	//
	SystemInputTransform(EntityComponentSystem& ecs)
		: System((GetComponentMask<CInput>() | GetComponentMask<CTransform>()))
		, _ecs(ecs) { }

	SystemInputTransform(const SystemInputTransform&) = delete;
	SystemInputTransform& operator=(const SystemInputTransform&) = delete;

	virtual void Update(scUint64 frameTime) override {
		auto& inputComponents = *_ecs.GetComponentArray<CInput>();
		auto& transformComponents = *_ecs.GetComponentArray<CTransform>();

		// Add a simple form of numerical integration (Explicit Euler) to speeds at different FPSs
		// (Explicit Euler works well as long as the speeds is constant or the frameTime is low)
		const float deltaSec = frameTime / 1000.0f;

		for (const auto& entityId : _entities) {
			auto& i = inputComponents[entityId];
			auto& t = transformComponents[entityId];

			// For each keykeyStates contains a value of 1 if pressed and a value of 0 if not pressed
			// Add negative and positive velocity so the sprite doesn't move if both are pressed at the same time
			sf::Vector2f tmpVelocity;
			tmpVelocity.x = ((-1.0f * i.KeyStates[sf::Keyboard::A]) + i.KeyStates[sf::Keyboard::D]);
			tmpVelocity.y = ((-1.0f * i.KeyStates[sf::Keyboard::W]) + i.KeyStates[sf::Keyboard::S]);

			// Normalize the velocity in case of diagonal movement
			// FIND SOME WAY TO DO THIS WITHOUT IF TO NOT DISTURB THE CACHE, OUR LORD AND SAVIOR
			if (tmpVelocity.x != 0 || tmpVelocity.y != 0)
				tmpVelocity = tmpVelocity.normalized();

			t.Velocity.x = (tmpVelocity.x * t.Speed) * deltaSec;
			t.Velocity.y = (tmpVelocity.y * t.Speed) * deltaSec;
			t.PositionAbs += t.Velocity;
		}
	}

private:
	EntityComponentSystem& _ecs;
};

}

#endif
