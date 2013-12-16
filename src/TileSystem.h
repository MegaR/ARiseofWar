#pragma once
#include "Tile.h"
#include "TileGrass.h"
#include "tileRocks.h"
#include "scene.h"

#include <vector>
#include <iostream>
using namespace std;
#include <stdlib.h>

#include <irrlicht.h>
using namespace irr;
using namespace core;

#define MAPSIZE 30

class TileSystem
{
public:
	TileSystem(void);
	~TileSystem(void);
	void create(Scene* scene);

	Tile* tiles[MAPSIZE][MAPSIZE];
};

