
#ifndef STONECOLD_ECS_SYSTEMCOLLISIONDETECTION_H
#define STONECOLD_ECS_SYSTEMCOLLISIONDETECTION_H

#include "System.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::ECS {

class SystemCollisionDetection : public System {
public:
	/*
		Effective (easy to compute) AABB Collision detection
		_____________________
		|		Box A		|		_____________________
		|					|  dX	|		Box B		|
		|		  x---------|-------|---------x			|
		|___________________|		|					|
				  x---------x		|___________________|
					 wA/2			x---------x
									   wB/2

		When the absolute distance (dX) between the centers 
		of both AABBs is less than the sum of the half-widths 
		(wA/2 + wB/2), there is a collision / overlap.
	*/

	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a CBoundingBox and CPosition component will be updated with this System
	//
	SystemCollisionDetection(EntityComponentSystem& ecs)
		: System((GetComponentMask<CBoundingBox>() | GetComponentMask<CPosition>()))
		, _ecs(ecs) { }

	SystemCollisionDetection(const SystemCollisionDetection&) = delete;
	SystemCollisionDetection& operator=(const SystemCollisionDetection&) = delete;

	virtual void Update(scUint64) override {
		auto& boundingBoxComponents = *_ecs.GetComponentArray<CBoundingBox>();
		auto& positionComponents = *_ecs.GetComponentArray<CPosition>();

		for (const auto& entityId : _entities) {
			auto& b = boundingBoxComponents[entityId];
			auto& p = positionComponents[entityId];
			b.Overlap = sf::Vector2f();

			for (const auto& checkEntityId : _entities) {
				auto& checkB = boundingBoxComponents[checkEntityId];
				auto& checkP = positionComponents[checkEntityId];

				// Do not compare AABB of the same entity or the same Type (type e.g.: MapTile to MapTile)
				if(entityId == checkEntityId || b.Type == checkB.Type)
					continue;

				const float deltaX = abs(p.PositionAbs.x - checkP.PositionAbs.x);
				const float deltaY = abs(p.PositionAbs.y - checkP.PositionAbs.y);
				const float overlapX = (b.BBSizeHalf.x + checkB.BBSizeHalf.x) - deltaX;
				const float overlapY = (b.BBSizeHalf.y + checkB.BBSizeHalf.y) - deltaY;
				b.Overlap = sf::Vector2f(overlapX, overlapY);
			}
		}
	}

	//
	// DEBUG RENDER OUTPUT
	// Draw all BoundingBoxes with a red frame
	//
	virtual scUint32 Render(sf::RenderTarget* renderTarget, const sf::View& camera) override {
		scUint32 drawCount = 0;
		auto& boundingBoxComponents = *_ecs.GetComponentArray<CBoundingBox>();
		auto& positionComponents = *_ecs.GetComponentArray<CPosition>();

		// Get the camera bounds to draw only Sprites that are in the current view
		const auto& camCenter = camera.getCenter();
		const auto& camSize = camera.getSize();
		const auto cameraRect = sf::FloatRect(sf::Vector2f(camCenter.x - (camSize.x / 2.f), camCenter.y - (camSize.y / 2.f)), camSize);

		for (const auto& entityId : _entities) {
			auto& b = boundingBoxComponents[entityId];
			auto& p = positionComponents[entityId];

			// Draw Rect if visible, based on the lastet transformation
			sf::RectangleShape rectangle(sf::Vector2f(b.BBSize.x - 3.f, b.BBSize.y - 3.f));
			rectangle.setPosition(p.PositionAbs);
			if(cameraRect.findIntersection(rectangle.getGlobalBounds())) {
				rectangle.setOutlineThickness(3.f);
				rectangle.setOutlineColor(sf::Color::Red);
				rectangle.setFillColor(sf::Color::Transparent);
				renderTarget->draw(rectangle);
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
