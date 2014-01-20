#include "Farm.h"
#include "Game.h" 


Farm::Farm(int tileX, int tileY, int player, Scene* scene) : Building(tileX, tileY, player, scene)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/buildingFarm.3ds");
	if (player == 0) {
		texture = game->videoDriver->getTexture("res/buildingFarm.png");
	} else { 
		texture = game->videoDriver->getTexture("res/buildingFarmEnemy.png");
	}

	sizeX = 1;
	sizeY = 1;
	createModel();
	node->setScale(vector3df(1.f, 1.f, 1.f));
	node->setRotation(vector3df(0,0,0));

	hp = 4;
	defense = 2;
}

Farm::~Farm(void) {
}

void  Farm::startTurn() {
	((GameScene*)scene)->players[player]->useResources(FARMINCREASE);
}
