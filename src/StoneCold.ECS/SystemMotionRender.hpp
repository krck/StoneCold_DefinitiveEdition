
#ifndef STONECOLD_ECS_SYSTEMMOTIONRENDER_H
#define STONECOLD_ECS_SYSTEMMOTIONRENDER_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::ECS {

class SystemMotionRender : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a Transformation and Velocity component will be updated with this System
	//
	SystemMotionRender(EntityComponentSystem& ecs)
		: System((GetComponentMask<CSprite>() | GetComponentMask<CTransform>()))
		, _ecs(ecs) { }

	SystemMotionRender(const SystemMotionRender&) = delete;
	SystemMotionRender& operator=(const SystemMotionRender&) = delete;

	virtual void Render(sf::RenderTarget* renderTarget, const sf::View& camera) override {
		auto& spriteComponents = *_ecs.GetComponentArray<CSprite>();
		auto& transformComponents = *_ecs.GetComponentArray<CTransform>();

		// Get the camera bounds to draw only Sprites that are in the current view
		const auto& camCenter = camera.getCenter();
		const auto& camSize = camera.getSize();
		const auto cameraRect = sf::FloatRect(sf::Vector2f(camCenter.x - (camSize.x / 2.f), camCenter.y - (camSize.y / 2.f)), camSize);

		for (const auto& entityId : _entities) {
			auto& s = spriteComponents[entityId];
			auto& t = transformComponents[entityId];

			// Transform (Scale, Flip and Move) the Sprite
			s.FlipSprite = (t.Velocity.x == 0 ? s.FlipSprite : (t.Velocity.x < 0 ? -1 : 1));
			s.Sprite->setScale({ (s.FlipSprite * t.Scale), (1.f * t.Scale) });
			s.Sprite->move(t.Velocity);

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
