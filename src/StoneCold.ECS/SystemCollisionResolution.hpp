
#ifndef STONECOLD_ECS_SYSTEMCOLLISIONRESOLUTION_H
#define STONECOLD_ECS_SYSTEMCOLLISIONRESOLUTION_H

#include "System.hpp"
#include "EntityComponentSystem.hpp"

#include <iostream>

namespace StoneCold::ECS {

class SystemCollisionResolution : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a CBoundingBox and CTransform component will be updated with this System
	//
	SystemCollisionResolution(EntityComponentSystem& ecs)
		: System((GetComponentMask<CBoundingBox>() | GetComponentMask<CTransform>()))
		, _ecs(ecs) { }

	SystemCollisionResolution(const SystemCollisionResolution&) = delete;
	SystemCollisionResolution& operator=(const SystemCollisionResolution&) = delete;

	virtual void Update(scUint64) override {
		auto& boundingBoxComponents = *_ecs.GetComponentArray<CBoundingBox>();
		//auto& transformComponents = *_ecs.GetComponentArray<CTransform>();

		for (const auto& entityId : _entities) {
			auto& b = boundingBoxComponents[entityId];
			//auto& t = transformComponents[entityId];

			if(b.Overlap.x > 0 && b.Overlap.y > 0)
				std::cout <<b.Overlap.x <<" - " <<b.Overlap.y <<std::endl;
		}
	}

private:
	EntityComponentSystem& _ecs;
};

}

#endif
