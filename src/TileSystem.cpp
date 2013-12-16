#include "TileSystem.h"
#include "Game.h"

TileSystem::TileSystem(void)
{
}

void TileSystem::create(Scene* scene) {
	cout << "Filling tilemap" << endl;
	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			if(rand() % 8 != 0 || ((GameScene*)scene)->getEntity(x,y)) {
				tiles[x][y] = new TileGrass(x,y);
			} else {
				tiles[x][y] = new TileRocks(x,y);
			}
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