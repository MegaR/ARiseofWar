#include "TileForrest.h"


TileForrest::TileForrest(int x, int y) : Tile(x, y) {
	createModel("res/tileForrest.3DS", "res/tileForrest.png", x, y);
	walkable = false;
}


TileForrest::~TileForrest(void)
{
}
