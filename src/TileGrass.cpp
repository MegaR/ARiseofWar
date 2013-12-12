#include "TileGrass.h"
#include "Game.h"

TileGrass::TileGrass(int x, int y) : Tile(x, y) {
	createModel("res/tileGrass.3DS", "res/tileGrassTexture.png", x, y);
}


TileGrass::~TileGrass(void)
{
}
