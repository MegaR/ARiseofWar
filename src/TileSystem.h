#pragma once
#include "Tile.h"
#include "TileGrass.h"

#include <vector>
#include <iostream>
using namespace std;

#include <irrlicht.h>
using namespace irr;
using namespace core;

#define MAPSIZE 30

class TileSystem
{
public:
	TileSystem(void);
	~TileSystem(void);

	Tile* tiles[MAPSIZE][MAPSIZE];
};

