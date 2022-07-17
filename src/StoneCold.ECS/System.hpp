
#ifndef STONECOLD_ECS_SYSTEM_H
#define STONECOLD_ECS_SYSTEM_H

#include <vector>
#include <iterator>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include "SceneAction.hpp"

namespace StoneCold::ECS {

using namespace StoneCold::Core;
using namespace StoneCold::Scenes;

//
// System Interface
//
class System {
public:
	System(scBitMask64 componentMask) : _componentMask(componentMask) { }
	System(const System&) = delete;
	System& operator=(const System&) = delete;

	virtual void HandleInput(const std::vector<SceneAction>&) { }
	virtual void Update(scUint64) { }
	virtual void Render(sf::RenderTarget*, sf::View*) { }

	inline scBitMask64 GetSystemMask() const { return _componentMask; }
	inline size_t GetEntitiesSize() const { return _entities.size(); }

	inline void AddEntity(scEntityId entityId) { if (std::find(_entities.begin(), _entities.end(), entityId) == _entities.end()) _entities.push_back(entityId); }
	inline void RemoveEntity(scEntityId entityId) { _entities.erase(std::remove(_entities.begin(), _entities.end(), entityId), _entities.end()); }

	virtual ~System() {}

protected:
	const scBitMask64 _componentMask;
	std::vector<scEntityId> _entities;
};

}

#endif
