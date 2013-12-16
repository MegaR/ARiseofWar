#include "TileSystem.h"
#include "Game.h"

TileSystem::TileSystem(void)
{
}

void TileSystem::create(Scene* scene) {
	cout << "Filling tilemap" << endl;
	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			int randInt = rand() % 10;
			if(randInt < 8 || ((GameScene*)scene)->getEntity(x,y)) {
				tiles[x][y] = new TileGrass(x,y);
			} else if(randInt < 9) {
				tiles[x][y] = new TileRocks(x,y);
			} else if(randInt < 10) {
				tiles[x][y] = new TileWheat(x,y);
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