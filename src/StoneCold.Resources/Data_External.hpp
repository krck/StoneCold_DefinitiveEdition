
#ifndef STONECOLD_DATAEXTERNAL_H
#define STONECOLD_DATAEXTERNAL_H

#include "Types.hpp"
#include <unordered_map>
#include <string>

//
// EXTERNAL DATA
//
// All data that needs to be loaded from the filesystem
// Stored as paths with corresponding string names
//
namespace StoneCold::Resources::Raw {

using namespace StoneCold::Base;

//
// All texture names as hardcoded, constant variables
//
static const std::string PLAYER_TEXTURE = "player\\Dwarf_Sprite.png";
static const std::string SKELETON_TEXTURE = "monsters\\Skeleton.png";
static const std::string STONECOLD_LOGO = "ui\\StoneCold.png";
static const std::string BACKGROUND_IMAGE = "ui\\the_mountain.png";
static const std::string GUI_TEXTURE = "ui\\gui_textures.png";

//
// All font names as hardcoded, constant variables
//
static const std::string FONT_CROM = "fonts\\Crom.ttf";

//
// All Map Textures hardcoded as unorderd_map
//
static const std::unordered_map<LevelType, std::string> MAP_TEXTURES = {
	{ LevelType::Grassland, "map\\grasslands.png" },
	{ LevelType::Desert, "map\\desert.png" },
	{ LevelType::Castle, "map\\castle.png" },
	{ LevelType::Highlands, "map\\highlands.png" },
	{ LevelType::Arctic, "map\\arctic.png" }
};

}

#endif
