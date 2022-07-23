
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
	// Only Entities with a CSprite, CStatic and CPosition component will be updated with this System
	//
	SystemStaticRender(EntityComponentSystem& ecs)
		: System((GetComponentMask<CSprite>() | GetComponentMask<CStatic>() | GetComponentMask<CPosition>()))
		, _ecs(ecs) { }

	SystemStaticRender(const SystemStaticRender&) = delete;
	SystemStaticRender& operator=(const SystemStaticRender&) = delete;

	virtual scUint32 Render(sf::RenderTarget* renderTarget, const sf::View& camera) override {
		scUint32 drawCount = 0;
		auto& spriteComponents = *_ecs.GetComponentArray<CSprite>();
		// auto& staticComponents = *_ecs.GetComponentArray<CStatic>();
		// auto& positionComponents = *_ecs.GetComponentArray<CPosition>();

		// Get the camera bounds to draw only Sprites that are in the current view
		const auto& camCenter = camera.getCenter();
		const auto& camSize = camera.getSize();
		const auto cameraRect = sf::FloatRect(sf::Vector2f(camCenter.x - (camSize.x / 2.f), camCenter.y - (camSize.y / 2.f)), camSize);

		for (const auto& entityId : _entities) {
			auto& sp = spriteComponents[entityId];
			// auto& st = staticComponents[entityId];
			// auto& p = positionComponents[entityId];

			// Scale and (based on movement direction) Flip the Sprite
			// sp.TextureRect = (sp.FlipSprite < 0
			// 	? sf::IntRect(sf::Vector2i(sp.TextureRect.left + sp.TextureRect.width, sp.TextureRect.top), sf::Vector2i(sp.TextureRect.width * -1.f, sp.TextureRect.height))
			// 	: sf::IntRect(sf::Vector2i(sp.TextureRect.left, sp.TextureRect.top), sf::Vector2i(sp.TextureRect.width, sp.TextureRect.height))
			// );
			// sp.Sprite->setScale({ st.Scale, st.Scale });
			// sp.Sprite->setPosition(p.PositionAbs);

			// Draw Sprite if visible, based on the lastet transformation
			if(cameraRect.findIntersection(sp.Sprite->getGlobalBounds())) {
				sp.Sprite->setTextureRect(sp.TextureRect);
				renderTarget->draw(*sp.Sprite);
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
