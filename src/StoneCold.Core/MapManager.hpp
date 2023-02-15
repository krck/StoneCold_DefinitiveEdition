
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

using namespace StoneCold::Common;

struct GameMap {
	std::vector<std::vector<MapTileType>> TileGrid;
	sf::Vector2f SpawnPoint;
	sf::Vector2f FinishPoint;
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

	scSptr<GameMap> GenerateMap(LevelType levelType, sf::Vector2i size);

	~MapManager() = default;

private:
	void CreateFloor(std::vector<std::vector<MapTileType>>& grid, float chanceWalkerChangeDir, float chanceWalkerUpdate);
	void CreateWalls(std::vector<std::vector<MapTileType>>& grid);
	std::pair<sf::Vector2i, sf::Vector2i> SetFinalMapTiles(std::vector<std::vector<MapTileType>>& grid);

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
	const std::vector<std::pair<float, float>> mapPatterns = {
		{ 0.6f, 0.01f }, // 1) ROCKY: Map with few open spaces, very jagged edges and lots of corridors and obstacles
		{ 0.75f, 0.1f }, // 2) MIXED: Map with bigger open spaces, some jagged edges and few obstacles
		{ 0.95f, 0.2f }	 // 3) FLAT: Map with one massive, open space, smoothe-ish edges and no corridors/obstacles
	};

};

}

#endif
