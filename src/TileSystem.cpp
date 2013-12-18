#include "TileSystem.h"
#include "Game.h"

TileSystem::TileSystem(void)
{
}

void TileSystem::create(Scene* scene) {
	GameScene* gameScene = (GameScene*)scene;
	cout << "Filling tilemap" << endl;
	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			tiles[x][y] = new TileGrass(x,y);
		}
	}

	int playerY = rand() % (MAPSIZE-4)+2;
	int playerX = rand() % 4+2;
	gameScene->entities.push_back(new TownCenter(playerX, playerY, 0));
	gameScene->entities.push_back(new UnitKnight(playerX+2, playerY, 0));
	gameScene->entities.push_back(new UnitKnight(playerX+2, playerY+1, 0));
	gameScene->entities.push_back(new UnitPeasant(playerX+2, playerY+2, 0));

	int enemyY = rand() % (MAPSIZE-4)+2;
	int enemyX = rand() % 4+2;
	gameScene->entities.push_back(new TownCenter(MAPSIZE-enemyX, enemyY, 1));
	gameScene->entities.push_back(new UnitKnight(MAPSIZE-enemyX-1, enemyY, 1));
	gameScene->entities.push_back(new UnitKnight(MAPSIZE-enemyX-1, enemyY+1, 1));
	gameScene->entities.push_back(new UnitPeasant(MAPSIZE-enemyX-1, enemyY+2, 1));
	
	generateStartResource(playerX, playerY, 0, scene);
	generateStartResource(playerX, playerY, 1, scene);
	generateStartResource(playerX, playerY, 2, scene);
	generateStartResource(MAPSIZE-enemyX, enemyY, 0, scene);
	generateStartResource(MAPSIZE-enemyX, enemyY, 1, scene);
	generateStartResource(MAPSIZE-enemyX, enemyY, 2, scene);

	for(int i = 0; i < RANDOMRESOURCECHUNKS; i ++) {
		int randomX = rand() % MAPSIZE;
		int randomY = rand() % MAPSIZE;
		spreadResource(randomX, randomY, rand()%3, scene, RANDOMRESOURCECHANCE);
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

void TileSystem::generateStartResource(int playerX, int playerY, int tileType, Scene* scene) {
	GameScene* gameScene = (GameScene*) scene;

	int randX;
	int randY;
	do {
		randX = rand()%4 + 3;
		randY = rand()%4 + 3;
		int random = rand()%4;
		
		switch(random) {
		case 0:
			randX = -randX;
			break;
		case 1:
			randY = -randY;
			break;
		case 2:
			randX = -randX;
			randY = -randY;
			break;
		}
		randX += playerX;
		randY += playerY;
	} while(gameScene->getEntity(randX, randY) || randX < 0 || randY < 0 || randX >= MAPSIZE || randY >= MAPSIZE );

	spreadResource(randX, randY, tileType, scene, STARTRESOURCECHANCE);
}

void TileSystem::spreadResource(int x, int y, int tileType, Scene* scene, int chance) {
	if(((GameScene*)scene)->getEntity(x, y)) return;

	delete tiles[x][y];
	switch(tileType) {
		case 0:	
			tiles[x][y] = new TileRocks(x, y);
			break;
		case 1:
			tiles[x][y] = new TileWheat(x, y);
			break;
		case 2:
			tiles[x][y] = new TileForrest(x, y);
			break;
	}

	if(rand()%100 < chance) {
		vector<vector2d<s32>>* neighbors = ((GameScene*)scene)->get_neighbors(vector2d<s32>(x,y));
		int randomDirection = rand();
		for(int i = 0; i < neighbors->size(); i++) {
			int ii = i + randomDirection % neighbors->size();
			if(((GameScene*)scene)->getEntity(neighbors->at(ii).X, neighbors->at(ii).Y) ) continue;

			spreadResource(neighbors->at(ii).X, neighbors->at(ii).Y, tileType, scene, chance - CHANCEDECREASE);
			break;
			
		}
		delete neighbors;
	}
}