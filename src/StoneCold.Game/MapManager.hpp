
#ifndef STONECOLD_MAPMANAGER_H
#define STONECOLD_MAPMANAGER_H

#include "Vec2.hpp"
#include <algorithm>
#include <iomanip>
#include <random>
#include <vector>

namespace StoneCold::Game {

using namespace StoneCold::Base;

//
// 2d procedural Map Generator
//
// Using the Drunkard-Walk procedural generation algorithm (The simplest dungeon map generator)
// This Code is based on a Tutorial by William Beaty (https://www.youtube.com/watch?v=I74I_MhZIK8)
// (... which in turn was based on the game Nuclear Throne)
//
class MapManager {
private:
	struct Walker { Vec2i dir = Vec2i(), pos = Vec2i(); };

public:
	MapManager() { }
	MapManager(const MapManager&) = delete;
	MapManager& operator=(const MapManager&) = delete;

	const std::vector<std::vector<MapTileTypes>>& GenerateMap(Vec2i size, float randomDirValue, float randomUpdateValue);
	inline std::pair<Vec2i, Vec2i> GetStartEndPositions() { return _mapStartEndPositions; }

	~MapManager() = default;

private:
	void CreateFloor(float chanceWalkerChangeDir, float chanceWalkerUpdate);
	void CreateWalls();
	void SetFinalMapTiles();

	//
	// Removes one element form a vector at the specified index
	//
	template <typename T>
	void remove_at(std::vector<T>& v, typename std::vector<T>::size_type i) {
		std::swap(v[i], v.back());
		v.pop_back();
	}

private:
	std::pair<Vec2i, Vec2i> _mapStartEndPositions;
	std::vector<std::vector<MapTileTypes>> _grid;
	std::vector<Walker> _walkers;
	Vec2i _mapSize;

	// Const map generation settings
	const int _maxWalkers = 10;
	const float _percentToFill = 0.35f;
};

}

#endif
