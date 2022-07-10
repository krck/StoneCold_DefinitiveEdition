
#ifndef STONECOLD_CORE_MAPTILEHELPER_H
#define STONECOLD_CORE_MAPTILEHELPER_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Enums.hpp"

namespace StoneCold::Core {

//
// Map Frames
// TileType mapping and "src rect" frames within any of the Map Textures (some need to be flipped as well)
//
static const auto MAP_TILE_FRAMES = std::unordered_map<MapTileTypes, std::pair<sf::IntRect, float>>({
	{ MapTileTypes::Wall_Top,				{ { sf::Vector2i(0,0), sf::Vector2i(32,32) },    1.f } },
	{ MapTileTypes::Corner_Top_Left,		{ { sf::Vector2i(32,0), sf::Vector2i(32,32) },  -1.f } },
	{ MapTileTypes::Corner_Top_Right,		{ { sf::Vector2i(32,0), sf::Vector2i(32,32) },   1.f } },
	{ MapTileTypes::Middle_Block_Vertical,	{ { sf::Vector2i(64,0), sf::Vector2i(32,32) },   1.f } },
	{ MapTileTypes::Endblock_Top,			{ { sf::Vector2i(96,0), sf::Vector2i(32,32) },   1.f } },
	{ MapTileTypes::Portal,					{ { sf::Vector2i(128,0), sf::Vector2i(32,32) },  1.f } },
	{ MapTileTypes::Top_Special,			{ { sf::Vector2i(0,32), sf::Vector2i(32,32) },   1.f } },
	{ MapTileTypes::Wall_Left,				{ { sf::Vector2i(32,32), sf::Vector2i(32,32) },  1.f } },
	{ MapTileTypes::Wall_Right,				{ { sf::Vector2i(32,32), sf::Vector2i(32,32) }, -1.f } },
	{ MapTileTypes::Middle_Block_Horizontal,{ { sf::Vector2i(64,32), sf::Vector2i(32,32) },  1.f } },
	{ MapTileTypes::Endblock_Bottom,		{ { sf::Vector2i(96,32), sf::Vector2i(32,32) },  1.f } },
	{ MapTileTypes::Floor_Special_3,		{ { sf::Vector2i(128,32), sf::Vector2i(32,32) }, 1.f } },
	{ MapTileTypes::Wall_Bottom,			{ { sf::Vector2i(0,64), sf::Vector2i(32,32) },   1.f } },
	{ MapTileTypes::Corner_Bottom_Left,		{ { sf::Vector2i(32,64), sf::Vector2i(32,32) }, -1.f } },
	{ MapTileTypes::Corner_Bottom_Right,	{ { sf::Vector2i(32,64), sf::Vector2i(32,32) },  1.f } },
	{ MapTileTypes::Floor_Special_2,		{ { sf::Vector2i(64,64), sf::Vector2i(32,32) },  1.f } },
	{ MapTileTypes::Endblock_Left,			{ { sf::Vector2i(96,64), sf::Vector2i(32,32) }, -1.f } },
	{ MapTileTypes::Endblock_Right,			{ { sf::Vector2i(96,64), sf::Vector2i(32,32) },  1.f } },
	{ MapTileTypes::Top_Default,			{ { sf::Vector2i(128,64), sf::Vector2i(32,32) }, 1.f } },
	{ MapTileTypes::Floor_Shadow,			{ { sf::Vector2i(0,96), sf::Vector2i(32,32) },   1.f } },
	{ MapTileTypes::Floor_Special_4,		{ { sf::Vector2i(32,96), sf::Vector2i(32,32) },  1.f } },
	{ MapTileTypes::Floor_Default,			{ { sf::Vector2i(64,96), sf::Vector2i(32,32) },  1.f } },
	{ MapTileTypes::Floor_Special_1,		{ { sf::Vector2i(96,96), sf::Vector2i(32,32) },  1.f } }
});

}

#endif
