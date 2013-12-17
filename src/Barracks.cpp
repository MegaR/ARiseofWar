#include "Barracks.h"
#include "Game.h"

Button* knightButton;

Barracks::Barracks(int tileX, int tileY, int player) : Building(tileX, tileY, player)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/buildingBarracks.3DS");
	texture = game->videoDriver->getTexture("res/buildingBarracks.png");
	sizeX = 2;
	sizeY = 2;
	createModel();
	node->setScale(vector3df(0.5f,0.5f,0.5f));
	node->setRotation(vector3df(0,30,0));
	GUI = game->gui->addImage(rect<s32>(0,0, 200, 100));
	GUI->setVisible(false);
	allowBuild = false;
	buildturn = 520;

	knightButton = new Button(10, 10, 75, 75, "knight", game->videoDriver->getTexture("res/guiButtonWide.png") );
	knightButton->btn->setVisible(false);
}


Barracks::~Barracks(void)
{
}

void Barracks::update(){
	addtoqueue();
	selected();
}

void Barracks::createUnit(){
	Game* game = &Game::getInstance();
	std::vector<vector2d<int>> *list = new std::vector<vector2d<int>>();
	
	list = ((GameScene*)game->currentScene)->get_neighbors(vector2d<s32>(tileX,tileY));
	if(list->size() > 0){
		((GameScene*)game->currentScene)->entities.push_back(new UnitKnight(list->at(0).X,list->at(0).Y, player ));
		delete list;
	}
}

void Barracks::addtoqueue(){
	Game* game = &Game::getInstance();
	
	if(game->eventReceiver->isKeyPressed(KEY_KEY_K) && allowBuild  == true ){
		buildturn = ((GameScene*)game->currentScene)->turnCount;
		cout << "pressed K" << endl; 
	}
}

void Barracks::selected(){
	Game* game = &Game::getInstance();
	
	if(((GameScene*)game->currentScene)->storedEntity  == this){
		GUI->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
		GUI->setVisible(true);
		knightButton->btn->setVisible(true);
		allowBuild = true;
	}
}

void Barracks::deselected(){
		GUI->setVisible(false);
		knightButton->btn->setVisible(false);
		allowBuild = false;
}

void  Barracks::startTurn(){
	Game* game = &Game::getInstance();
	cout << buildturn << endl;
	if((buildturn+4)== ((GameScene*)game->currentScene)->turnCount){
		createUnit();
		cout<< "this was true" << endl;
	}
}