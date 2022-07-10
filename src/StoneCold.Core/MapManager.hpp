
#ifndef STONECOLD_CORE_MAPMANAGER_H
#define STONECOLD_CORE_MAPMANAGER_H

#include <random>
#include <vector>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Enums.hpp"
#include "Types.hpp"

namespace StoneCold::Core {

struct GameMap {
	std::vector<std::vector<MapTileTypes>> TileGrid;
	sf::Vector2i SpawnPoint;
	sf::Vector2i FinishPoint;
};

//
// 2D procedural Map Generator
//
// Using the Drunkard-Walk procedural generation algorithm (The simplest dungeon map generator)
// This Code is based on a Tutorial by William Beaty (https://www.youtube.com/watch?v=I74I_MhZIK8)
// (... which in turn was based on the game Nuclear Throne)
//
class MapManager {
private:
	struct Walker { sf::Vector2i dir = sf::Vector2i(), pos = sf::Vector2i(); };

public:
	MapManager() { }
	MapManager(const MapManager&) = delete;
	MapManager& operator=(const MapManager&) = delete;

	scSptr<GameMap> GenerateMap(sf::Vector2i size, float randomDirValue, float randomUpdateValue);

	~MapManager() = default;

private:
	void CreateFloor(std::vector<std::vector<MapTileTypes>>& grid, float chanceWalkerChangeDir, float chanceWalkerUpdate);
	void CreateWalls(std::vector<std::vector<MapTileTypes>>& grid);
	std::pair<sf::Vector2i, sf::Vector2i> SetFinalMapTiles(std::vector<std::vector<MapTileTypes>>& grid);

	//
	// Removes one element form a vector at the specified index
	//
	template <typename T>
	void remove_at(std::vector<T>& v, typename std::vector<T>::size_type i) {
		std::swap(v[i], v.back());
		v.pop_back();
	}

private:
	sf::Vector2i _mapSize;
	std::vector<Walker> _walkers;

	// Const map generation settings
	const int _maxWalkers = 10;
	const float _percentToFill = 0.35f;

public:
	//
	// Map Frames
	// TileType mapping and "src rect" frames within any of the Map Textures (some need to be flipped as well)
	//
	const std::unordered_map<MapTileTypes, std::pair<sf::IntRect, float>> MAP_TILE_FRAMES = 
		std::unordered_map<MapTileTypes, std::pair<sf::IntRect, float>>({
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

};

}

#endif
