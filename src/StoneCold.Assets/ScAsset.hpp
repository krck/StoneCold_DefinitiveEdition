
#ifndef STONECOLD_ASSETS_SCASSET_H
#define STONECOLD_ASSETS_SCASSET_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Types.hpp"

namespace StoneCold::Assets {

using namespace StoneCold::Core;

class ScAsset {
public:
	ScAsset(const std::string& name) : Id(std::hash<std::string>()(name)), Name(name) {}

public:
	const scHash Id;
	const std::string Name;
};

}

#endif
