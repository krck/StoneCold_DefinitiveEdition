
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
	// Only Entities with a CSprite and CTransform component will be updated with this System
	//
	SystemMotionRender(EntityComponentSystem& ecs)
		: System((GetComponentMask<CSprite>() | GetComponentMask<CTransform>()))
		, _ecs(ecs) { }

	SystemMotionRender(const SystemMotionRender&) = delete;
	SystemMotionRender& operator=(const SystemMotionRender&) = delete;

	virtual scUint32 Render(sf::RenderTarget* renderTarget, const sf::View& camera) override {
		scUint32 drawCount = 0;
		auto& spriteComponents = *_ecs.GetComponentArray<CSprite>();
		auto& transformComponents = *_ecs.GetComponentArray<CTransform>();

		// Get the camera bounds to draw only Sprites that are in the current view
		const auto& camCenter = camera.getCenter();
		const auto& camSize = camera.getSize();
		const auto cameraRect = sf::FloatRect(sf::Vector2f(camCenter.x - (camSize.x / 2.f), camCenter.y - (camSize.y / 2.f)), camSize);

		for (const auto& entityId : _entities) {
			auto& s = spriteComponents[entityId];
			auto& t = transformComponents[entityId];

			// Transform the Sprite
			s.Sprite->setScale(sf::Vector2f(t.Scale, t.Scale));
			s.Sprite->move(t.Velocity);

			// Draw Sprite if visible, based on the lastet transformation
			if(cameraRect.findIntersection(s.Sprite->getGlobalBounds())) {
				// Flip the Sprit, in case of movement direction change (left/rigt)
				// (This is done by simply flipping the "width" part of the current TextureRect)
				s.FlipSprite = (t.Velocity.x == 0 ? s.FlipSprite : (t.Velocity.x < 0 ? -1.f : 1.f));
				s.TextureRect = (s.FlipSprite < 0
								? sf::IntRect(sf::Vector2i(s.TextureRect.left + s.TextureRect.width, s.TextureRect.top), sf::Vector2i(s.TextureRect.width * -1.f, s.TextureRect.height))
								: sf::IntRect(sf::Vector2i(s.TextureRect.left, s.TextureRect.top), sf::Vector2i(s.TextureRect.width, s.TextureRect.height))
				);
				s.Sprite->setTextureRect(s.TextureRect);
				renderTarget->draw(*s.Sprite);
				drawCount++;
			}
		}
		return drawCount;
	}

private:
	EntityComponentSystem& _ecs;
};

}

#endif
