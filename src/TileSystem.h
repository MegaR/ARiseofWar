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

	Tile* tiles[MAPSIZE][MAPSIZE];
};

