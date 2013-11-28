#include "UnitKnight.h"

#include "Game.h"

#include <iostream>
using namespace std;

UnitKnight::UnitKnight(int _x, int _y, int _player)
{
	tileX = _x;
	tileY = _y;
	player = _player; 
	hp = 10;
	attack = 4;
	defense = 3;
	maxDistance = 5;
	attackDistance = 1;
	
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("C:/irrlicht-1.8/media/sydney.md2");
	modelNode = game->sceneManager->addAnimatedMeshSceneNode( model );
	if (modelNode)
    {
        modelNode->setMaterialFlag(EMF_LIGHTING, false);
        modelNode->setMD2Animation(scene::EMAT_STAND);
		modelNode->setMaterialTexture( 0, game->videoDriver->getTexture("C:/irrlicht-1.8/media/sydney.bmp") );
		modelNode->setID(0);
		modelNode->setPosition(vector3df(tileX * 10, 0, tileY * 10));
    }

	selected = false;
}

UnitKnight::~UnitKnight()
{
	//Game::getInstance().sceneManager->addToDeletionQueue(model);
	Game::getInstance().sceneManager->addToDeletionQueue(modelNode);
	cout << "destroyed Knight" << endl;
}