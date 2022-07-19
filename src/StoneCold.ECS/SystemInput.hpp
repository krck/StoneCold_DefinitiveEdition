
#ifndef STONECOLD_ECS_SYSTEMINPUT_H
#define STONECOLD_ECS_SYSTEMINPUT_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::ECS {

using namespace StoneCold::Scenes;

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

	virtual void HandleInput(const std::vector<SceneAction>& actions) override {
		auto& inputComponents = *_ecs.GetComponentArray<CInput>();

		for (const auto& entityId : _entities) {
			auto& i = inputComponents[entityId];
			
			// Transform all input actions into a simple lookup by action name
			for (const auto& a : actions) {
				i.Actions[a.GetAction()] = a.GetType();
			}
		}
	}

private:
	EntityComponentSystem& _ecs;
};

}

#endif
