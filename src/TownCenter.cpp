#include "TownCenter.h"
#include "Game.h"

TownCenter::TownCenter(int tileX, int tileY, int player) : Building(tileX, tileY, player)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/buildingTownCenter.md2");
	texture = game->videoDriver->getTexture("res/buildingTownCenter.png");
	sizeX = 2;
	sizeY = 2;
	createModel();
}


TownCenter::~TownCenter(void)
{
}
