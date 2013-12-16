#include "TileWheat.h"


TileWheat::TileWheat(int x, int y) : Tile(x,y)
{
	createModel("res/tileWheat.3DS", "res/tileWheat.png", x, y);
	walkable = false;
}


TileWheat::~TileWheat(void)
{
}
