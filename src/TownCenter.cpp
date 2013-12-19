#include "TownCenter.h"
#include "Game.h"
TownCenter::TownCenter(int tileX, int tileY, int player) : Building(tileX, tileY, player)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/buildingTownCenter.md2");
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/buildingTownCenter.png");
	} else {
		texture = game->videoDriver->getTexture("res/buildingTownCenterEnemy.png");
	}
	sizeX = 2;
	sizeY = 2;
	hp = 10;
	defense = 2;
	createModel();
	node->setRotation(vector3df(0,15,0));
	GUI = game->gui->addImage(rect<s32>(0,0, 300, 125));
	txt =	game->gui->addStaticText(L"peasant duurt 1 beurt om te bouwen" ,rect<s32>(0,0, 300, 100));
	GUI->setVisible(false); 
	txt->setVisible(false);
	allowBuild = true;
	buildturn = 420;

	peasantButton = new Button(120, 35, 75, 75, "peasant", game->videoDriver->getTexture("res/guiButtonCreate.png") );
	peasantButton->btn->setVisible(false);
}


TownCenter::~TownCenter(void)
{
	Game* game = &Game::getInstance();
	GUI->remove();
	txt->remove();
	delete peasantButton;
	if(player == 0){
		((GameScene*)game->currentScene)->enemyunits =true;
	}else if( player == 1){
		((GameScene*)game->currentScene)->playerunits = true;
	}

}

void TownCenter::update(){
	peasantButton->update();
	addtoqueue();
}

void TownCenter::createUnit(){
	Game* game = &Game::getInstance();
	GameScene* scene = (GameScene*)game->currentScene;
	std::vector<vector2d<int>> *list;
	
	allowBuild = true;
	list = this->getSurroundingTiles();
	for(int i = 0; i < list->size(); i++) {
		TileGrass* tile = dynamic_cast<TileGrass*>(scene->tilesystem.tiles[list->at(i).X][list->at(i).Y]);

		if( scene->getEntity(list->at(i).X, list->at(i).Y) || !tile) {
			list->erase(list->begin()+i);
			i--;
		}
	}
	if(list->size() > 0){
		((GameScene*)game->currentScene)->entities.push_back(new UnitPeasant(list->at(0).X,list->at(0).Y, player ));
		delete list;
	}
}

void TownCenter::addtoqueue(){
	Game* game = &Game::getInstance();
	
	if((game->eventReceiver->isKeyPressed(KEY_KEY_P) || peasantButton->pressed) && allowBuild  == true ){
		buildturn = ((GameScene*)game->currentScene)->turnCount;
		cout << "queued" << endl; 
		allowBuild = false;
	}

}

void TownCenter::selected(){
	Game* game = &Game::getInstance();
	if(player != 0) return;
	
	GUI->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
	GUI->setVisible(true);
	txt->setVisible(true);
	peasantButton->btn->setVisible(true);
}

void TownCenter::deselected(){
		GUI->setVisible(false);
		txt->setVisible(false);
		peasantButton->btn->setVisible(false);
}

void TownCenter::startTurn(){
	Game* game = &Game::getInstance();
	
	if((buildturn+2)== ((GameScene*)game->currentScene)->turnCount){
		createUnit();
		
		cout<< "this was true" << endl;
	}
}

void TownCenter::enemyTurn() {
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;
	if(allowBuild && rand()%5 == 0) {
		buildturn = scene->turnCount;
		allowBuild = false;
	}
}