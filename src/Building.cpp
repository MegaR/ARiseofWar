#include "Building.h"
#include "Game.h"

Building::Building(int tileX, int tileY) : Entity()
{
	this->tileX = tileX;
	this->tileY = tileY;
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
		
	meshNode->setPosition(vector3df(tileX*10-(5*(sizeX/2)), 0.0f, tileY*10-(5*(sizeY/2))));
	node = meshNode;
}