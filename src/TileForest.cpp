#include "TileForest.h"


TileForest::TileForest(int x, int y) : Tile(x, y) {
	createModel("res/tileForest.3DS", "res/tileForest.png", x, y);
	walkable = false;
}


TileForest::~TileForest(void)
{
}
