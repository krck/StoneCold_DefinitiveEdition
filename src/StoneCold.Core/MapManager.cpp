
#include "MapManager.hpp"

using namespace StoneCold::Core;
using namespace StoneCold::Common;

scSptr<GameMap> MapManager::GenerateMap(LevelType levelType, sf::Vector2i size) {
	GameMap map;
	_mapSize = size;
	_walkers = std::vector<Walker>();

	// Get a Pre-defined map pattern
	std::pair<float, float> pattern = { 0.f, 0.f };
	switch (levelType)
	{
		// Grassland and Arctic can be FLAT or MIXED (1 || 2)
		case LevelType::Grassland:	pattern = mapPatterns[(rand() & 1) + 1]; 	break;
		case LevelType::Arctic:		pattern = mapPatterns[(rand() & 1) + 1]; 	break;
		// Highlands or Desert can be ROCKY or MIXED (0 || 1)
		case LevelType::Highlands:	pattern = mapPatterns[(rand() & 1)]; 		break;
		case LevelType::Desert:		pattern = mapPatterns[(rand() & 1)]; 		break;
		// Castle can only be ROCKY (0)
		case LevelType::Castle:		pattern = mapPatterns[0]; 					break;
		default: 					pattern = mapPatterns[0];					break;
	}

	// Create a grid with empty spaces and the generate the random map into it
	map.TileGrid = std::vector<std::vector<MapTileType>>(_mapSize.x, std::vector<MapTileType>(_mapSize.y, MapTileType::Top_Default));
	CreateFloor(map.TileGrid, pattern.first, pattern.second);
	CreateWalls(map.TileGrid);
	auto mapPoints = SetFinalMapTiles(map.TileGrid);

	map.SpawnPoint = sf::Vector2f(mapPoints.first);
	map.FinishPoint = sf::Vector2f(mapPoints.second);

	return std::make_shared<GameMap>(map);
}

void MapManager::CreateFloor(std::vector<std::vector<MapTileType>>& grid, float chanceWalkerChangeDir, float chanceWalkerUpdate) {
	const auto mapCenter = sf::Vector2i((_mapSize.x / 2), (_mapSize.y / 2));
	// Setup the random directions to pick from
	const std::vector<sf::Vector2i> directions = {
		sf::Vector2i(0, -1),	// down
		sf::Vector2i(-1, 0),	// left
		sf::Vector2i(0, 1),		// up
		sf::Vector2i(1, 0)		// right 
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
			walker.pos.x += walker.dir.x;
			walker.pos.y += walker.dir.y;
			// Avoid the boarder of the grid
			// Clamp x,y to leave space to the boarder (7 Tiles) and if it hits that threshold: Reset to the center of the map
			walker.pos.x = (std::clamp<scInt32>(walker.pos.x, 7, _mapSize.x - 8) != walker.pos.x ? mapCenter.x : walker.pos.x);
			walker.pos.y = (std::clamp<scInt32>(walker.pos.y, 7, _mapSize.y - 8) != walker.pos.y ? mapCenter.y : walker.pos.y);

			// Create a Floor at the position of every walker, if there is non already
			if (grid[walker.pos.x][walker.pos.y] != MapTileType::Floor_Default) {
				grid[walker.pos.x][walker.pos.y] = MapTileType::Floor_Default;
				floorCount++;
			}
		}

		// Random chance: Spawn a new Walker (Only if # of _walkers < max, and at a low chance)
		random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		if (random < chanceWalkerUpdate && _walkers.size() < (scUint64)_maxWalkers) {
			auto newWalker = Walker();
			newWalker.dir = directions[(rand() % 4 + 1) - 1];
			newWalker.pos = _walkers.front().pos;
			_walkers.push_back(newWalker);
		}

		// Calculate the Percentage of tiles that are "Floor" and exit if enough is filled
		if ((floorCount / (float)(_mapSize.x * _mapSize.y)) > _percentToFill)
			return;
	}
}

void MapManager::CreateWalls(std::vector<std::vector<MapTileType>>& grid) {
	// Loop though every grid space and check if theres a floor, with
	// empty space around it. This will be changed to a Wall-Placeholder
	for (scUint64 i = 0; i < grid.size(); i++) {
		for (scUint64 j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == MapTileType::Floor_Default) {
				if (grid[i - 1][j] == MapTileType::Top_Default) {
					grid[i - 1][j] = MapTileType::Placeholder;
				}
				if (grid[i + 1][j] == MapTileType::Top_Default) {
					grid[i + 1][j] = MapTileType::Placeholder;
				}
				if (grid[i][j - 1] == MapTileType::Top_Default) {
					grid[i][j - 1] = MapTileType::Placeholder;
				}
				if (grid[i][j + 1] == MapTileType::Top_Default) {
					grid[i][j + 1] = MapTileType::Placeholder;
				}
			}
		}
	}
}

std::pair<sf::Vector2i, sf::Vector2i> MapManager::SetFinalMapTiles(std::vector<std::vector<MapTileType>>& grid) {
	const int lastFloorType = static_cast<int>(MapTileType::Floor_Shadow);
	auto topTile = MapTileType::Top_Default;
	auto spawnPositions = std::vector<sf::Vector2i>();
	auto floorCheck = std::vector<bool>();

	// Loop the whole Map and update any Wall-Placeholder to its actual Tile-Type
	for (scUint64 i = 0; i < grid.size(); i++) {
		for (scUint64 j = 0; j < grid[i].size(); j++) {
			// If Wall-Placeholder:
			// Check all the Floor Tiles nearby and update the Placeholder to a specific Type of Wall
			if (grid[i][j] == MapTileType::Placeholder) {
				floorCheck = {
					grid[i - 1][j] == MapTileType::Floor_Default,	// top
					grid[i + 1][j] == MapTileType::Floor_Default,	// bottom
					grid[i][j - 1] == MapTileType::Floor_Default,	// right
					grid[i][j + 1] == MapTileType::Floor_Default	// left
				};
				// Switch based on the Count of surrounding Floor-Tiles
				switch (floorCheck[0] + floorCheck[1] + floorCheck[2] + floorCheck[3])
				{
				case 4:
					// If Wall is completely surrounded by Floor tiles: Replace it with Floor (Clear all single walls)
					grid[i][j] = MapTileType::Floor_Default;
					break;
				case 3:
					// If floor is in 3 locations around: Must be a "Endblock"
					if (!floorCheck[0]) grid[i][j] = MapTileType::Endblock_Bottom;
					else if (!floorCheck[1]) grid[i][j] = MapTileType::Endblock_Top;
					else if (!floorCheck[2]) grid[i][j] = MapTileType::Endblock_Right;
					else grid[i][j] = MapTileType::Endblock_Left;
					break;
				case 2:
					// If floor is in 2 locations around: Must be a "Corner" or "Middle-Block"
					if (floorCheck[0] && floorCheck[2]) grid[i][j] = MapTileType::Corner_Top_Left;
					else if (floorCheck[0] && floorCheck[3]) grid[i][j] = MapTileType::Corner_Top_Right;
					else if (floorCheck[1] && floorCheck[2]) grid[i][j] = MapTileType::Corner_Bottom_Left;
					else if (floorCheck[1] && floorCheck[3]) grid[i][j] = MapTileType::Corner_Bottom_Right;
					else if (floorCheck[0] && floorCheck[1]) grid[i][j] = MapTileType::Middle_Block_Horizontal;
					else grid[i][j] = MapTileType::Middle_Block_Vertical;
					break;
				case 1:
					// If floor is in 1 location around: Must be a "Normal" Wall-Block
					if (floorCheck[0]) grid[i][j] = MapTileType::Wall_Top;
					else if (floorCheck[1]) grid[i][j] = MapTileType::Wall_Bottom;
					else if (floorCheck[2]) grid[i][j] = MapTileType::Wall_Right;
					else grid[i][j] = MapTileType::Wall_Left;
					break;
				default: break;
				}
			}

			// Save all the possible spawn positions. Always below a Endblock_Bottom
			if (grid[i][j] == MapTileType::Endblock_Bottom)
				spawnPositions.push_back(sf::Vector2i(static_cast<int>(j), static_cast<int>(i + 1)));
		}
	}

	// Loop one last time, to update the Floor and Top Tiles (add Shadow, random Specials, ...)
	for (scUint64 i = 1; i < grid.size() - 1; i++) {
		for (scUint64 j = 1; j < grid[i].size() - 1; j++) {
			// If Top:
			// Check if there is at least one Wall nearby and change the Default-Top to the Special-Top
			if (grid[i][j] == MapTileType::Top_Default) {
				if (static_cast<int>(grid[i - 1][j]) > lastFloorType
					|| static_cast<int>(grid[i + 1][j]) > lastFloorType
					|| static_cast<int>(grid[i][j - 1]) > lastFloorType
					|| static_cast<int>(grid[i][j + 1]) > lastFloorType) {
					grid[i][j] = MapTileType::Top_Special;
				}
			}
			// If Floor-Placeholder
			// Check if Floor is below a Wall and replace with the Shadow-Tile and just randomize the Specials
			else if (grid[i][j] == MapTileType::Floor_Default) {
				topTile = grid[i - 1][j];
				if (topTile == MapTileType::Wall_Bottom
					|| topTile == MapTileType::Middle_Block_Horizontal
					|| topTile == MapTileType::Corner_Bottom_Right
					|| topTile == MapTileType::Corner_Bottom_Left
					|| topTile == MapTileType::Endblock_Bottom
					|| topTile == MapTileType::Endblock_Right
					|| topTile == MapTileType::Endblock_Left) {
					grid[i][j] = MapTileType::Floor_Shadow;
				}
				else {
					switch (rand() % 100 + 1)
					{
					case 1: grid[i][j] = MapTileType::Floor_Special_1; break;
					case 2: grid[i][j] = MapTileType::Floor_Special_2; break;
					case 3: grid[i][j] = MapTileType::Floor_Special_3; break;
					case 4: grid[i][j] = MapTileType::Floor_Special_4; break;
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
	grid[start.y][start.x] = MapTileType::Portal;
	grid[end.y][end.x] = MapTileType::Portal;
	return std::make_pair(start, end);
}
