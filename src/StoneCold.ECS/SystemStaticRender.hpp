
#ifndef STONECOLD_ECS_SYSTEMSTATICRENDER_H
#define STONECOLD_ECS_SYSTEMSTATICRENDER_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::ECS {

class SystemStaticRender : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a Transformation and Velocity component will be updated with this System
	//
	SystemStaticRender(EntityComponentSystem& ecs)
		: System((GetComponentMask<CSprite>() | GetComponentMask<CStaticPosition>()))
		, _ecs(ecs) { }

	SystemStaticRender(const SystemStaticRender&) = delete;
	SystemStaticRender& operator=(const SystemStaticRender&) = delete;

	virtual void Render(sf::RenderTarget* renderTarget, const sf::View& camera) override {
		auto& spriteComponents = *_ecs.GetComponentArray<CSprite>();
		auto& staticComponents = *_ecs.GetComponentArray<CStaticPosition>();

		// Get the camera bounds to draw only Sprites that are in the current view
		const auto& camCenter = camera.getCenter();
		const auto& camSize = camera.getSize();
		const auto cameraRect = sf::FloatRect(sf::Vector2f(camCenter.x - (camSize.x / 2.f), camCenter.y - (camSize.y / 2.f)), camSize);

		for (const auto& entityId : _entities) {
			auto& s = spriteComponents[entityId];
			auto& p = staticComponents[entityId];

			// Scale and (based on movement direction) Flip the Sprite
			s.Sprite->setScale({ (s.FlipSprite * p.Scale), (1.f * p.Scale) });
			s.Sprite->setPosition(p.PositionAbs);

			// Draw Sprite if visible, based on the lastet transformation
			if(cameraRect.findIntersection(s.Sprite->getGlobalBounds())) {
				s.Sprite->setTextureRect(s.TextureRect);
				renderTarget->draw(*s.Sprite);
			}
		}
	}

private:
	EntityComponentSystem& _ecs;
};

}

#endif
