#include "Barracks.h"
#include "Game.h"

Barracks::Barracks(int tileX, int tileY) : Building(tileX, tileY)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/barracks.3DS");
	texture = game->videoDriver->getTexture("res/barracks.tga");
	sizeX = 2;
	sizeY = 2;
	createModel();
}


Barracks::~Barracks(void)
{
}
