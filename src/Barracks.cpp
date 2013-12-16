#include "Barracks.h"
#include "Game.h"

Barracks::Barracks(int tileX, int tileY, int player) : Building(tileX, tileY, player)
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

void Barracks::update(){
	createUnit();
}

void Barracks::createUnit(){
	Game* game = &Game::getInstance();
	if(game->eventReceiver->isKeyPressed(KEY_KEY_K)){
		std::vector<vector2d<int>> *list = new std::vector<vector2d<int>>();

		list = ((GameScene*)game->currentScene)->get_neighbors(vector2d<s32>(tileX,tileY));
		if(list->size() > 0){
			((GameScene*)game->currentScene)->entities.push_back(new UnitKnight(list->at(0).X,list->at(0).Y, 1));
		}
		delete list;
	}
}