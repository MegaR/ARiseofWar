#include "tileRocks.h"


#include "Game.h"

TileRocks::TileRocks(int x, int y) : Tile(x, y) {
	createModel("res/tileRocks.3DS", "res/tilerocks.png", x, y);
	walkable = false;
}


TileRocks::~TileRocks(void)
{
}
