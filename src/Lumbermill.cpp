#include "Lumbermill.h"
#include "Game.h" 


Lumbermill::Lumbermill(int tileX, int tileY, int player, Scene* scene) : Building(tileX, tileY, player, scene)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/buildingLumbermill.md2");
	if (player == 0) { texture = game->videoDriver->getTexture("res/buildingLumbermill.png"); }
	else { texture = game->videoDriver->getTexture("res/buildingLumbermill.png"); }
	sizeX = 1;
	sizeY = 1;
	createModel();
	node->setScale(vector3df(0.69f,0.69f,0.69f));
	node->setRotation(vector3df(0,30,0));

	hp = 4;
	defense = 2;
}


Lumbermill::~Lumbermill(void)
{
}
