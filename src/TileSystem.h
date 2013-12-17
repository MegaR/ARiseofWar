#pragma once
#include "Tile.h"
#include "TileGrass.h"
#include "tileRocks.h"
#include "TileWheat.h"
#include "scene.h"

#include "UnitPeasant.h"

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
	void generateStartResource(int playerX, int playerY, int tileType, Scene* scene);
	void spreadResource(int x, int y, int tileType, Scene* scene, int chance);

	Tile* tiles[MAPSIZE][MAPSIZE];
};

