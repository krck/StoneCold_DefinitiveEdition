
#ifndef STONECOLD_SCENES_SCENEACTION_H
#define STONECOLD_SCENES_SCENEACTION_H

#include <string>
#include <utility>
#include "Enums.hpp"

namespace StoneCold::Scenes {

using namespace StoneCold::Common;

class SceneAction  {
public:
	SceneAction(ActionMap id, ActionType type, const std::string& action) : _id(id), _type(type), _action(action) { }
	SceneAction(const SceneAction& rhs) : _id(rhs.GetId()), _type(rhs.GetType()), _action(rhs.GetAction()) { }

	//
	// Assignment Operator (aka. The Tricky One)
	// In a class with no benefit from memory reuse (no heap-allocated members, std::vector, etc.)
	// the most convenient Assignment-Operator implementation is based on the Copy-and-Swap idiom:
	// - Pass by value so it can be called as Copy OR Move Assignment Operator
	// - Strong exception guarantee: rhs wont be modified directly and does not throw  
	//
	SceneAction& operator=(SceneAction rhs) noexcept { _id = rhs.GetId(); _type = rhs.GetType(); _action = rhs.GetAction();  return *this; }

	inline ActionMap GetId() const { return _id; }
	inline ActionType GetType() const { return _type; }
	inline std::string GetAction() const { return _action; }

private:
	ActionMap _id;
	ActionType _type;
	std::string _action;
};

}

#endif
