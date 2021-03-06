#include "Lumbermill.h"
#include "Game.h" 


LumberMill::LumberMill(int tileX, int tileY, int player, Scene* scene) : Building(tileX, tileY, player, scene)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/buildingLumbermill.md2");
	if (player == 0) {
		texture = game->videoDriver->getTexture("res/buildingLumbermill.png");
	} else { 
		texture = game->videoDriver->getTexture("res/buildingLumbermillEnemy.png");
	}

	sizeX = 1;
	sizeY = 1;
	createModel();
	node->setScale(vector3df(1.25f, 1.25f, 1.25f));
	node->setRotation(vector3df(0,10,0));

	hp = 4;
	defense = 2;
}

LumberMill::~LumberMill(void)
{
}

void  LumberMill::startTurn(){
	((GameScene*)scene)->players[player]->useResources(LUMBERMILLINCREASE);
}
