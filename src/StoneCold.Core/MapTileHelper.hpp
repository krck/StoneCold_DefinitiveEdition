
#ifndef STONECOLD_CORE_MAPTILEHELPER_H
#define STONECOLD_CORE_MAPTILEHELPER_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Enums.hpp"

namespace StoneCold::Core {

struct MapTileRenderInfo {
	std::string TileTypeStr;
	sf::IntRect TileTextureRect;
	float TileTextureFlip;
};

//
// Map Frames
// TileType mapping and "src rect" frames within any of the Map Textures (some need to be flipped as well)
//
static const auto MapTileRenderInfos = std::unordered_map<MapTileType, MapTileRenderInfo>({
	{ MapTileType::Wall_Top,				{ "Wall_Top",{  				sf::Vector2i(0,0), sf::Vector2i(32,32) },    1.f } },
	{ MapTileType::Corner_Top_Left,			{ "Corner_Top_Left",{  			sf::Vector2i(32,0), sf::Vector2i(32,32) },  -1.f } },
	{ MapTileType::Corner_Top_Right,		{ "Corner_Top_Right",{  		sf::Vector2i(32,0), sf::Vector2i(32,32) },   1.f } },
	{ MapTileType::Middle_Block_Vertical,	{ "Middle_Block_Vertical",{  	sf::Vector2i(64,0), sf::Vector2i(32,32) },   1.f } },
	{ MapTileType::Endblock_Top,			{ "Endblock_Top",{  			sf::Vector2i(96,0), sf::Vector2i(32,32) },   1.f } },
	{ MapTileType::Portal,					{ "Portal",{  					sf::Vector2i(128,0), sf::Vector2i(32,32) },  1.f } },
	{ MapTileType::Top_Special,				{ "Top_Special",{  				sf::Vector2i(0,32), sf::Vector2i(32,32) },   1.f } },
	{ MapTileType::Wall_Left,				{ "Wall_Left",{  				sf::Vector2i(32,32), sf::Vector2i(32,32) },  1.f } },
	{ MapTileType::Wall_Right,				{ "Wall_Right",{  				sf::Vector2i(32,32), sf::Vector2i(32,32) }, -1.f } },
	{ MapTileType::Middle_Block_Horizontal,	{ "Middle_Block_Horizontal",{ 	sf::Vector2i(64,32), sf::Vector2i(32,32) },  1.f } },
	{ MapTileType::Endblock_Bottom,			{ "Endblock_Bottom",{  			sf::Vector2i(96,32), sf::Vector2i(32,32) },  1.f } },
	{ MapTileType::Floor_Special_3,			{ "Floor_Special_3",{  			sf::Vector2i(128,32), sf::Vector2i(32,32) }, 1.f } },
	{ MapTileType::Wall_Bottom,				{ "Wall_Bottom",{  				sf::Vector2i(0,64), sf::Vector2i(32,32) },   1.f } },
	{ MapTileType::Corner_Bottom_Left,		{ "Corner_Bottom_Left",{  		sf::Vector2i(32,64), sf::Vector2i(32,32) }, -1.f } },
	{ MapTileType::Corner_Bottom_Right,		{ "Corner_Bottom_Right",{  		sf::Vector2i(32,64), sf::Vector2i(32,32) },  1.f } },
	{ MapTileType::Floor_Special_2,			{ "Floor_Special_2",{  			sf::Vector2i(64,64), sf::Vector2i(32,32) },  1.f } },
	{ MapTileType::Endblock_Left,			{ "Endblock_Left",{  			sf::Vector2i(96,64), sf::Vector2i(32,32) }, -1.f } },
	{ MapTileType::Endblock_Right,			{ "Endblock_Right",{  			sf::Vector2i(96,64), sf::Vector2i(32,32) },  1.f } },
	{ MapTileType::Top_Default,				{ "Top_Default",{  				sf::Vector2i(128,64), sf::Vector2i(32,32) }, 1.f } },
	{ MapTileType::Floor_Shadow,			{ "Floor_Shadow",{  			sf::Vector2i(0,96), sf::Vector2i(32,32) },   1.f } },
	{ MapTileType::Floor_Special_4,			{ "Floor_Special_4",{ 		 	sf::Vector2i(32,96), sf::Vector2i(32,32) },  1.f } },
	{ MapTileType::Floor_Default,			{ "Floor_Default",{  			sf::Vector2i(64,96), sf::Vector2i(32,32) },  1.f } },
	{ MapTileType::Floor_Special_1,			{ "Floor_Special_1",{  			sf::Vector2i(96,96), sf::Vector2i(32,32) },  1.f } }
});

}

#endif
