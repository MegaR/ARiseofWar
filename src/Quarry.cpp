#include "Quarry.h"
#include "Game.h" 


Quarry::Quarry(int tileX, int tileY, int player, Scene* scene) : Building(tileX, tileY, player, scene)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/buildingQuarry.3ds");
	if (player == 0) {
		texture = game->videoDriver->getTexture("res/buildingQuarry.png");
	} else { 
		texture = game->videoDriver->getTexture("res/buildingQuarryEnemy.png");
	}

	sizeX = 1;
	sizeY = 1;
	createModel();
	node->setScale(vector3df(1.25f, 1.25f, 1.25f));
	node->setRotation(vector3df(0,10,0));

	hp = 4;
	defense = 2;
}

Quarry::~Quarry(void)
{
}

void  Quarry::startTurn(){
	((GameScene*)scene)->players[player]->useResources(QUARRYINCREASE);
}
