#include "TownCenter.h"
#include "Game.h"
TownCenter::TownCenter(int tileX, int tileY, int player, Scene* scene) : Building(tileX, tileY, player, scene)
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
	GUI = game->gui->addImage(rect<s32>(0,40, 275, 135));
	GUI->setImage(game->videoDriver->getTexture("res/guiPeasant.png"));
	txt = game->gui->addStaticText(L"Het duurt 1 beurt om de Peasant te maken." ,rect<s32>(95, 50, 265, 125));
	GUI->setVisible(false); 
	txt->setVisible(false);
	buildturn = -1;

	peasantButton = new Button(10, 50, 75, 75, "Peasant", "Wood: 5\nFood: 5\nStone: 5\nGold: 0", game->videoDriver->getTexture("res/guiButtonCreate.png") );
	peasantButton->btn->setVisible(false);

	if(player == 0) {
		cameraFocus();
	}
}


TownCenter::~TownCenter(void)
{
	Game* game = &Game::getInstance();
	GUI->remove();
	txt->remove();
	delete peasantButton;

}

void TownCenter::update(){
	Game* game = &Game::getInstance();
	if(player == 0 && game->eventReceiver->isKeyPressed(KEY_KEY_H) ) {
		this->cameraFocus();
	}
	peasantButton->update();
	addtoqueue();
}

void TownCenter::createUnit(){
	Game* game = &Game::getInstance();
	GameScene* scene = (GameScene*)game->currentScene;
	std::vector<vector2d<int>> *list;
	
	list = this->getSurroundingTiles();
	for(int i = 0; i < list->size(); i++) {
		TileGrass* tile = dynamic_cast<TileGrass*>(scene->tilesystem.tiles[list->at(i).X][list->at(i).Y]);

		if( scene->getEntity(list->at(i).X, list->at(i).Y) || !tile) {
			list->erase(list->begin()+i);
			i--;
		}
	}
	if(list->size() > 0){
		((GameScene*)scene)->entities.push_back(new UnitPeasant(list->at(0).X,list->at(0).Y, player, scene ));
		delete list;

	}
}

void TownCenter::addtoqueue(){
	Game* game = &Game::getInstance();
	
	if((game->eventReceiver->isKeyPressed(KEY_KEY_P) || peasantButton->pressed) && allowBuild()){
		buildturn = ((GameScene*)scene)->turnCount + (PEASANTBUILDTIME);
		((GameScene*)scene)->players[player]->useResources(PEASANTCOST);
		peasantButton->btn->setEnabled(false);
		cout << "queued peasant" << endl;
	}

}

void TownCenter::selected(){
	Game* game = &Game::getInstance();
	if(player != 0) return;
	
	GUI->setVisible(true);
	txt->setVisible(true);
	peasantButton->btn->setVisible(true);
	if(allowBuild()) {
		peasantButton->btn->setEnabled(true);
	} else {
		peasantButton->btn->setEnabled(false);
	}
}

void TownCenter::deselected(){
		GUI->setVisible(false);
		txt->setVisible(false);
		peasantButton->btn->setVisible(false);
}

void TownCenter::startTurn(){
	Player* player = ((GameScene*)scene)->players[this->player];
	player->useResources(defaultincome);
	if(buildturn != -1 && buildturn <= ((GameScene*)scene)->turnCount){
		createUnit();
		buildturn = -1;
	}
}

bool TownCenter::enemyTurn() {
	int numPeasants = 0;
	for(int i = 0; i < ((GameScene*)scene)->entities.size(); i++) {
		if(dynamic_cast<UnitPeasant*>( ((GameScene*)scene)->entities[i]) ) {
			if(((GameScene*)scene)->entities[i]->player == 1) {
				numPeasants++;
			}
		}
	}

	if(allowBuild() && numPeasants < 2) {
		buildturn = ((GameScene*)scene)->turnCount + PEASANTBUILDTIME;
		((GameScene*)scene)->players[player]->useResources(PEASANTCOST);
	} 
	return false;
}

bool TownCenter::allowBuild() {
	Player* player = ((GameScene*)scene)->players[this->player];
	if(!player->hasResources(PEASANTCOST)) {
		return false;
	}

	if(buildturn > ((GameScene*)scene)->turnCount) {
		return false;
	}
	return true;
}