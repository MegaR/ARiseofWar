#include "Building.h"
#include "Game.h"

Building::Building(int tileX, int tileY, int player) : Entity()
{
	this->tileX = tileX;
	this->tileY = tileY;
	this->player = player;
}


Building::~Building(void)
{
}

void Building::createModel() {
	IMeshSceneNode* meshNode = Game::getInstance().sceneManager->addMeshSceneNode( model );
	meshNode->setMaterialTexture( 0, texture );
	meshNode->getMaterial(0).Shininess = 0;
	meshNode->addShadowVolumeSceneNode(0, 0, false);
	meshNode->setID(0);
		
	meshNode->setPosition(vector3df(tileX*10+(5*(sizeX/2)), 0.0f, tileY*10+(5*(sizeY/2))));
	node = meshNode;
}

std::vector<vector2d<int>>* Building::getSurroundingTiles() {
	vector<vector2d<int>>* tiles = new vector<vector2d<int>>();

	for(int x = 0; x < sizeX; x++) {
		if(tileX+x >= MAPSIZE) continue;
		if(tileY-1 > 0) tiles->push_back(vector2d<int>(tileX+x,tileY-1) );
		if(tileY+sizeY < MAPSIZE) tiles->push_back(vector2d<int>(tileX+x,tileY+sizeY) );
	}

	for(int y = 0; y < sizeY; y++) {
		if(tileY+y >= MAPSIZE) continue;
		if(tileX-1 > 0) tiles->push_back(vector2d<int>(tileX-1,tileY+y) );
		if(tileX+sizeX < MAPSIZE) tiles->push_back(vector2d<int>(tileX+sizeX,tileY+y) );
	}

	return tiles;
}

bool Building::inAttackRange(int x, int y, int attackDistance) {
	for(int offsetX = 0; offsetX < sizeX; offsetX++) {
		for(int offsetY = 0; offsetY < sizeY; offsetY++) {
			cout << sizeX;
			int calcX = abs(tileX+offsetX-x);
			int calcY = abs(tileY+offsetY-y);
			if ((calcX+calcY)<=attackDistance) return true;
		}
	}
	return false;
}