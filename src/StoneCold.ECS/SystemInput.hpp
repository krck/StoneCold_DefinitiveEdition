
#ifndef STONECOLD_ECS_SYSTEMINPUT_H
#define STONECOLD_ECS_SYSTEMINPUT_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::ECS {

class SystemInput : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a Transformation and Velocity component will be updated with this System
	//
	SystemInput(EntityComponentSystem& ecs)
		: System(GetComponentMask<CInput>())
		, _ecs(ecs) { }

	SystemInput(const SystemInput&) = delete;
	SystemInput& operator=(const SystemInput&) = delete;

	virtual void HandleInput() override {
		auto& inputComponents = *_ecs.GetComponentArray<CInput>();

		for (const auto& entityId : _entities) {
			auto& i = inputComponents[entityId];

			// Movement related Keys
			i.KeyStates[sf::Keyboard::A] 		= sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			i.KeyStates[sf::Keyboard::D] 		= sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			i.KeyStates[sf::Keyboard::W] 		= sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			i.KeyStates[sf::Keyboard::S] 		= sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			i.KeyStates[sf::Keyboard::LShift] 	= sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
			i.KeyStates[sf::Keyboard::Space] 	= sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
			// Action related Keys
			i.KeyStates[sf::Keyboard::Num1] 	= sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
			i.KeyStates[sf::Keyboard::Num2] 	= sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
			i.KeyStates[sf::Keyboard::Num3] 	= sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
			i.KeyStates[sf::Keyboard::Num4] 	= sf::Keyboard::isKeyPressed(sf::Keyboard::Num4);
		}
	}

private:
	EntityComponentSystem& _ecs;
};

}

#endif
