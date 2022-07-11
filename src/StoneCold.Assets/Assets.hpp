
#ifndef STONECOLD_ASSETS_ASSET_H
#define STONECOLD_ASSETS_ASSET_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Types.hpp"

namespace StoneCold::Assets {

using namespace StoneCold::Core;

class Asset {
public:
	Asset(const std::string& name) : Id(std::hash<std::string>()(name)), Name(name) {}

public:
	const scHash Id;
	const std::string Name;
};

}

#endif
