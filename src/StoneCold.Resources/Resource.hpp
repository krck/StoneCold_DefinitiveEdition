
#ifndef STONECOLD_RES_RESOURCE_H
#define STONECOLD_RES_RESOURCE_H

#include <string>
#include <functional>
#include "Types.hpp"

namespace StoneCold::Resources {

class Resource {
public:
	Resource(const std::string& name) : Id(std::hash<std::string>()(name)), Name(name) {}

public:
	const StoneCold::Core::scHash Id;
	const std::string Name;
};

}

#endif
