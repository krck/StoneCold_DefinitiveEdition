
#include "MapManager.hpp"

using namespace StoneCold;
using namespace StoneCold::Game;


const std::vector<std::vector<MapTileTypes>>& MapManager::GenerateMap(Vec2i size, float randomDirValue, float randomUpdateValue) {
	// Set _grid size and create a _grid with empty spaces and reset the _walkers
	_mapSize = size;
	_grid = std::vector<std::vector<MapTileTypes>>(_mapSize.X, std::vector<MapTileTypes>(_mapSize.Y, MapTileTypes::Top_Default));
	_walkers = std::vector<Walker>();

	CreateFloor(randomDirValue, randomUpdateValue);
	CreateWalls();
	SetFinalMapTiles();

	return _grid;
}


void MapManager::CreateFloor(float chanceWalkerChangeDir, float chanceWalkerUpdate) {
	const auto mapCenter = Vec2i((_mapSize.X / 2), (_mapSize.Y / 2));
	// Setup the random directions to pick from
	const std::vector<Vec2i> directions = {
		Vec2i(0, -1),	// down
		Vec2i(-1, 0),	// left
		Vec2i(0, 1),	// up
		Vec2i(1, 0)		// right 
	};

	// Create and add the first walker (spawn in the center)
	auto newWalker = Walker();
	newWalker.dir = directions[(rand() % 4 + 1) - 1];
	newWalker.pos = mapCenter;
	_walkers.push_back(newWalker);

	float random = 0.f;
	float floorCount = 0.f;
	for (int iterations = 0; iterations < 100000; iterations++) {
		// Random chance: Destroy a Walker (Only if its not the only one, and at a low chance)
		random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		if (random < chanceWalkerUpdate && _walkers.size() > 1) {
			remove_at(_walkers, (rand() % ((_walkers.size() - 1) + 0)));
		}

		// Move all _walkers
		for (auto& walker : _walkers) {
			// Random chance: Walker picks a new direction
			random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			if (random < chanceWalkerChangeDir)
				walker.dir = directions[(rand() % 4 + 1) - 1];

			// Update the position, based on the direction
			walker.pos.X += walker.dir.X;
			walker.pos.Y += walker.dir.Y;
			// Avoid the boarder of the _grid
			// Clamp x,y to leave space to the boarder (7 Tiles) and if it hits that threshold: Reset to the center of the map
			walker.pos.X = (std::clamp<uint32>(walker.pos.X, 7, _mapSize.X - 8) != walker.pos.X ? mapCenter.X : walker.pos.X);
			walker.pos.Y = (std::clamp<uint32>(walker.pos.Y, 7, _mapSize.Y - 8) != walker.pos.Y ? mapCenter.Y : walker.pos.Y);

			// Create a Floor at the position of every walker, if there is non already
			if (_grid[walker.pos.X][walker.pos.Y] != MapTileTypes::Floor_Default) {
				_grid[walker.pos.X][walker.pos.Y] = MapTileTypes::Floor_Default;
				floorCount++;
			}
		}

		// Random chance: Spawn a new Walker (Only if # of _walkers < max, and at a low chance)
		random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		if (random < chanceWalkerUpdate && _walkers.size() < _maxWalkers) {
			auto newWalker = Walker();
			newWalker.dir = directions[(rand() % 4 + 1) - 1];
			newWalker.pos = _walkers.front().pos;
			_walkers.push_back(newWalker);
		}

		// Calculate the Percentage of tiles that are "Floor" and exit if enough is filled
		if ((floorCount / (float)(_mapSize.X * _mapSize.Y)) > _percentToFill)
			return;
	}
}


void MapManager::CreateWalls() {
	// Loop though every _grid space and check if theres a floor, with
	// empty space around it. This will be changed to a Wall-Placeholder
	for (uint64 i = 0; i < _grid.size(); i++) {
		for (uint64 j = 0; j < _grid[i].size(); j++) {
			if (_grid[i][j] == MapTileTypes::Floor_Default) {
				if (_grid[i - 1][j] == MapTileTypes::Top_Default) {
					_grid[i - 1][j] = MapTileTypes::Placeholder;
				}
				if (_grid[i + 1][j] == MapTileTypes::Top_Default) {
					_grid[i + 1][j] = MapTileTypes::Placeholder;
				}
				if (_grid[i][j - 1] == MapTileTypes::Top_Default) {
					_grid[i][j - 1] = MapTileTypes::Placeholder;
				}
				if (_grid[i][j + 1] == MapTileTypes::Top_Default) {
					_grid[i][j + 1] = MapTileTypes::Placeholder;
				}
			}
		}
	}
}


void MapManager::SetFinalMapTiles() {
	const int lastFloorType = static_cast<int>(MapTileTypes::Floor_Shadow);
	auto topTile = MapTileTypes::Top_Default;
	auto spawnPositions = std::vector<Vec2i>();
	auto floorCheck = std::vector<bool>();

	// Loop the whole Map and update any Wall-Placeholder to its actual Tile-Type
	for (uint64 i = 0; i < _grid.size(); i++) {
		for (uint64 j = 0; j < _grid[i].size(); j++) {
			// If Wall-Placeholder:
			// Check all the Floor Tiles nearby and update the Placeholder to a specific Type of Wall
			if (_grid[i][j] == MapTileTypes::Placeholder) {
				floorCheck = {
					_grid[i - 1][j] == MapTileTypes::Floor_Default,	// top
					_grid[i + 1][j] == MapTileTypes::Floor_Default,	// bottom
					_grid[i][j - 1] == MapTileTypes::Floor_Default,	// right
					_grid[i][j + 1] == MapTileTypes::Floor_Default	// left
				};
				// Switch based on the Count of surrounding Floor-Tiles
				switch (floorCheck[0] + floorCheck[1] + floorCheck[2] + floorCheck[3])
				{
				case 4:
					// If Wall is completely surrounded by Floor tiles: Replace it with Floor (Clear all single walls)
					_grid[i][j] = MapTileTypes::Floor_Default;
					break;
				case 3:
					// If floor is in 3 locations around: Must be a "Endblock"
					if (!floorCheck[0]) _grid[i][j] = MapTileTypes::Endblock_Bottom;
					else if (!floorCheck[1]) _grid[i][j] = MapTileTypes::Endblock_Top;
					else if (!floorCheck[2]) _grid[i][j] = MapTileTypes::Endblock_Right;
					else _grid[i][j] = MapTileTypes::Endblock_Left;
					break;
				case 2:
					// If floor is in 2 locations around: Must be a "Corner" or "Middle-Block"
					if (floorCheck[0] && floorCheck[2]) _grid[i][j] = MapTileTypes::Corner_Top_Left;
					else if (floorCheck[0] && floorCheck[3]) _grid[i][j] = MapTileTypes::Corner_Top_Right;
					else if (floorCheck[1] && floorCheck[2]) _grid[i][j] = MapTileTypes::Corner_Bottom_Left;
					else if (floorCheck[1] && floorCheck[3]) _grid[i][j] = MapTileTypes::Corner_Bottom_Right;
					else if (floorCheck[0] && floorCheck[1]) _grid[i][j] = MapTileTypes::Middle_Block_Horizontal;
					else _grid[i][j] = MapTileTypes::Middle_Block_Vertical;
					break;
				case 1:
					// If floor is in 1 location around: Must be a "Normal" Wall-Block
					if (floorCheck[0]) _grid[i][j] = MapTileTypes::Wall_Top;
					else if (floorCheck[1]) _grid[i][j] = MapTileTypes::Wall_Bottom;
					else if (floorCheck[2]) _grid[i][j] = MapTileTypes::Wall_Right;
					else _grid[i][j] = MapTileTypes::Wall_Left;
					break;
				default: break;
				}
			}

			// Save all the possible spawn positions. Always below a Endblock_Bottom
			if (_grid[i][j] == MapTileTypes::Endblock_Bottom)
				spawnPositions.push_back(Vec2i(static_cast<int>(j), static_cast<int>(i + 1)));
		}
	}

	// Loop one last time, to update the Floor and Top Tiles (add Shadow, random Specials, ...)
	for (uint64 i = 1; i < _grid.size() - 1; i++) {
		for (uint64 j = 1; j < _grid[i].size() - 1; j++) {
			// If Top:
			// Check if there is at least one Wall nearby and change the Default-Top to the Special-Top
			if (_grid[i][j] == MapTileTypes::Top_Default) {
				if (static_cast<int>(_grid[i - 1][j]) > lastFloorType
					|| static_cast<int>(_grid[i + 1][j]) > lastFloorType
					|| static_cast<int>(_grid[i][j - 1]) > lastFloorType
					|| static_cast<int>(_grid[i][j + 1]) > lastFloorType) {
					_grid[i][j] = MapTileTypes::Top_Special;
				}
			}
			// If Floor-Placeholder
			// Check if Floor is below a Wall and replace with the Shadow-Tile and just randomize the Specials
			else if (_grid[i][j] == MapTileTypes::Floor_Default) {
				topTile = _grid[i - 1][j];
				if (topTile == MapTileTypes::Wall_Bottom
					|| topTile == MapTileTypes::Middle_Block_Horizontal
					|| topTile == MapTileTypes::Corner_Bottom_Right
					|| topTile == MapTileTypes::Corner_Bottom_Left
					|| topTile == MapTileTypes::Endblock_Bottom
					|| topTile == MapTileTypes::Endblock_Right
					|| topTile == MapTileTypes::Endblock_Left) {
					_grid[i][j] = MapTileTypes::Floor_Shadow;
				}
				else {
					switch (rand() % 100 + 1)
					{
					case 1: _grid[i][j] = MapTileTypes::Floor_Special_1; break;
					case 2: _grid[i][j] = MapTileTypes::Floor_Special_2; break;
					case 3: _grid[i][j] = MapTileTypes::Floor_Special_3; break;
					case 4: _grid[i][j] = MapTileTypes::Floor_Special_4; break;
					default: break;
					}
				}
			}
		}
	}

	// Set the Map-Start and Map-End Positions based on all possible spawnPoints
	// (Take the first and last so they are as far away from each other as possible)
	auto start = spawnPositions.front();
	auto end = spawnPositions.back();
	_grid[start.Y][start.X] = MapTileTypes::Portal;
	_grid[end.Y][end.X] = MapTileTypes::Portal;
	_mapStartEndPositions = { start, end };
}
