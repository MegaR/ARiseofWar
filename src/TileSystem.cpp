#include "TileSystem.h"


TileSystem::TileSystem(void)
{
	cout << "Filling tilemap" << endl;
	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			tiles[x][y] = new TileGrass();
		}
	}
}



TileSystem::~TileSystem(void)
{
	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			delete tiles[x][y];
		}
	}
}
