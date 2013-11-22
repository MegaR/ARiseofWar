#pragma once
#include "Tile.h"

#include <irrlicht.h>
using namespace irr;
using namespace core;

#include <iostream>
using namespace std;

class TileGrass : public Tile
{
public:
	TileGrass(int x = 0, int y = 0);
	~TileGrass(void);
};

