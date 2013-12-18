#include "TownCenter.h"
#include "Game.h"

Button* peasantButton;


TownCenter::TownCenter(int tileX, int tileY, int player) : Building(tileX, tileY, player)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/buildingTownCenter.md2");
	texture = game->videoDriver->getTexture("res/buildingTownCenter.png");
	sizeX = 2;
	sizeY = 2;
	createModel();

	node->setScale(vector3df(0.5f,0.5f,0.5f));
	node->setRotation(vector3df(0,30,0));
	GUI = game->gui->addImage(rect<s32>(0,0, 300, 125));
	txt =	game->gui->addStaticText(L"peasant duurt 1 burten om te bouwen" ,rect<s32>(0,0, 300, 100));
	GUI->setVisible(false); 
	txt->setVisible(false);
	allowBuild = false;
	buildturn = 520;

	peasantButton = new Button(120, 35, 75, 75, "peasant", game->videoDriver->getTexture("res/guiButtonWide.png") );
	peasantButton->btn->setVisible(false);
}


TownCenter::~TownCenter(void)
{
	GUI->remove();
	txt->remove();
	//delete peasantButton;
	peasantButton->btn->setVisible(false);

}

void TownCenter::update(){
	peasantButton->update();
	addtoqueue();
}

void TownCenter::createUnit(){

	Game* game = &Game::getInstance();
	std::vector<vector2d<int>> *list = new std::vector<vector2d<int>>();
	
	list = ((GameScene*)game->currentScene)->get_neighbors(vector2d<s32>(tileX,tileY));
	if(list->size() > 0){
		((GameScene*)game->currentScene)->entities.push_back(new UnitPeasant(list->at(0).X,list->at(0).Y, player ));
		delete list;
	}
}

void TownCenter::addtoqueue(){
	Game* game = &Game::getInstance();
	
	if((game->eventReceiver->isKeyPressed(KEY_KEY_P) || peasantButton->pressed) && allowBuild  == true ){
		buildturn = ((GameScene*)game->currentScene)->turnCount;
		cout << "pressed P" << endl; 
	}

}

void TownCenter::selected(){
	Game* game = &Game::getInstance();
	
	GUI->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
	GUI->setVisible(true);
	txt->setVisible(true);
	peasantButton->btn->setVisible(true);
	allowBuild = true;
}

void TownCenter::deselected(){
		GUI->setVisible(false);
		txt->setVisible(false);
		peasantButton->btn->setVisible(false);
		allowBuild = false;
}

void TownCenter::startTurn(){
	Game* game = &Game::getInstance();
	cout << buildturn << endl;
	if((buildturn+4)== ((GameScene*)game->currentScene)->turnCount){
		createUnit();
		cout<< "this was true" << endl;
	}
}