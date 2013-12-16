#include "Barracks.h"
#include "Game.h"

Barracks::Barracks(int tileX, int tileY, int player) : Building(tileX, tileY, player)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/buildingBarracks.3DS");
	texture = game->videoDriver->getTexture("res/buildingBarracks.png");
	sizeX = 2;
	sizeY = 2;
	createModel();
	GUI = game->gui->addImage(rect<s32>(0,0, 200, 100));
	GUI->setImage(game->videoDriver->getTexture("res/background.png"));
}


Barracks::~Barracks(void)
{
}

void Barracks::update(){
	createUnit();
	selected();
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

void Barracks::selected(){
	Game* game = &Game::getInstance();
	
	if(((GameScene*)game->currentScene)->storedEntity  == this){
		
		GUI->setVisible(true);
	}
}

void Barracks::deselected(){
		GUI->setVisible(false);
}
