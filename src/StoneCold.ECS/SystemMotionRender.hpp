
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

	virtual void Render(sf::RenderTarget* renderTarget) override {
		auto& spriteComponents = *_ecs.GetComponentArray<CSprite>();
		auto& transformComponents = *_ecs.GetComponentArray<CTransform>();

		for (const auto& entityId : _entities) {
			auto& s = spriteComponents[entityId];
			auto& t = transformComponents[entityId];

			// Scale and (based on movement direction) Flip the Sprite
			s.FlipSprite = (t.Velocity.x == 0 ? s.FlipSprite : (t.Velocity.x < 0 ? -1 : 1));
			s.Sprite->setScale({ (s.FlipSprite * t.Scale), (1.f * t.Scale) });

			// Transform and draw the SFML Sprite
			s.Sprite->move(t.Velocity);
			s.Sprite->setTextureRect(s.TextureRect);
			renderTarget->draw(*s.Sprite);
		}
	}

private:
	EntityComponentSystem& _ecs;
};

}

#endif
