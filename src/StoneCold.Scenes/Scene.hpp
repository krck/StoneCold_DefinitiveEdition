
#ifndef STONECOLD_SCENES_SCENE_H
#define STONECOLD_SCENES_SCENE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "AssetManager.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::Scenes {

using namespace StoneCold::ECS;
using namespace StoneCold::Core;
using namespace StoneCold::Assets;

//
// Scene Interface
//
class Scene  {
public:
	Scene(scUint32 maxEntities, AssetManager& assetManager) 
		: _ecs(EntityComponentSystem(maxEntities)), _assetManager(assetManager) { }

	inline EntityComponentSystem* GetECS() { return &_ecs; }

	virtual bool Initialize() = 0;

	virtual void Start()  { _isActive = true; } // = 0;
	virtual void Stop() { _isActive = false; } // = 0;
	inline bool IsActive() const { return _isActive; }

	virtual bool HandleEvent() = 0;
	virtual void HandleInput() = 0;
	virtual void SimulateUpdate() { }
	virtual void Update(scUint32 frameTime) = 0;
	virtual void Render(sf::RenderTarget* renderTarget, sf::View* camera) = 0;

protected:
	bool _isActive;
	EntityComponentSystem _ecs;
	AssetManager& _assetManager;
};

}

#endif
