#pragma once
#include "Tile.h"
#include "TileGrass.h"

#include <vector>
#include <iostream>
using namespace std;

#define MAPSIZE 30

class TileSystem
{
public:
	TileSystem(void);
	~TileSystem(void);
	std::vector<vector2d<int>>* findPath(vector2d<int> start, vector2d<int> end);

	Tile* tiles[MAPSIZE][MAPSIZE];

private:

	//pathfinding
	int findElement(std::vector<vector2d<int>> list, vector2d<int> element); 
	vector2d<int> lowest(int list[][MAPSIZE]);
	std::vector<vector2d<int>>* get_neighbors(vector2d<int> current);
	int heuristic_cost_estimate(vector2d<int> current, vector2d<int> goal);
	std::vector<vector2d<int>>* reconstructed_path(vector2d<int> came_from[][MAPSIZE], vector2d<int> end, vector2d<int> start);
};

