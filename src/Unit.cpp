#include "Unit.h"

#include "Game.h"
#include <iostream>
using namespace std;

Unit::Unit(int tileX, int tileY, int player)
{
	this->tileX = tileX;
	this->tileY = tileY;
	this->player = player;

	node = Game::getInstance().sceneManager->addEmptySceneNode(0, 0);
	node->setPosition(vector3df(tileX * 10, 0, tileY * 10) );
}

Unit::~Unit()
{
	cout << "destroying Unit" << endl;
	while(modelNodes.size() > 0) {
		removeModel();
	}
}


void Unit::moveTo(int desX, int desY)
{
	/*int distanceX = desX - tileX, 
		distanceY = desY - tileY;*/
	/*
	if (tileX < desX)
	{
		//moveAnimation
		tileX++;
	}
	else if (tileX > desX)
	{
		//moveAnimation
		tileX--;
	}
	else //tileX == desX (unit is at target)
	{
		//idleAnimation
		tileX = desX;
	}
	
	if (tileY < desY)
	{
		//moveAnimation
		tileY++;
	}
	else if (tileY > desY)
	{
		//moveAnimation
		tileY--;
	}
	else //tileY == desY (unit is at target)
	{
		//idleAnimation
		tileY = desY;
	}
	*/
	tileX = desX;
	tileY = desY;
	node->setPosition(vector3df(tileX * 10, 0, tileY * 10));
}

void Unit::attackTarget(Entity* target)
{
	if (target->defense >= attack)
	{
		//attackAnimation
		target->hp--;
	}
	else
	{
		//attackAnimation
		target->hp -= (attack - target->defense);
	}
}

int randSeedCount = 0;
void Unit::addModel() {
	IAnimatedMeshSceneNode* modelNode = Game::getInstance().sceneManager->addAnimatedMeshSceneNode( model, node );
	if (modelNode)
    {
        modelNode->setMaterialFlag(EMF_LIGHTING, false);
        modelNode->setMD2Animation(scene::EMAT_STAND);
		modelNode->setMaterialTexture( 0, Game::getInstance().videoDriver->getTexture("C:/irrlicht-1.8/media/sydney.bmp") );
		modelNode->setID(0);
		modelNode->setScale(vector3df(0.2f, 0.2f, 0.2f) );
		
		srand(time(NULL)+randSeedCount++);
		float randX = rand() % 8 - 4;
		srand(time(NULL)+randSeedCount++);
		float randZ =rand() % 8 - 4;
		modelNode->setPosition(vector3df(randX, 5, randZ));
    }

	modelNodes.push_back(modelNode);
}

void Unit::removeModel() {
	IAnimatedMeshSceneNode* modelNode = modelNodes[modelNodes.size()-1];
	modelNodes.pop_back();
	Game::getInstance().sceneManager->addToDeletionQueue(modelNode);
}