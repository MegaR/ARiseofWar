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
	GUI = game->gui->addImage(rect<s32>(0,0, 300, 125));
	txt =	game->gui->addStaticText(L"Peasant duurt 2 beurten om te bouwen" ,rect<s32>(0,0, 300, 100));
	GUI->setVisible(false); 
	txt->setVisible(false);
	buildturn = -1;

	peasantButton = new Button(120, 35, 75, 75, "peasant", game->videoDriver->getTexture("res/guiButtonCreate.png") );
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
	if(player == 0){
		((GameScene*)game->currentScene)->enemyunits = true;
	}else if( player == 1){
		((GameScene*)game->currentScene)->playerunits = true;
	}

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
		buildturn = ((GameScene*)scene)->turnCount + PEASANTBUILDTIME;
		((GameScene*)scene)->players[player]->useResources(PEASANTCOST);
		peasantButton->btn->setEnabled(false);
		cout << "queued peasant" << endl;
	}

}

void TownCenter::selected(){
	Game* game = &Game::getInstance();
	if(player != 0) return;
	
	GUI->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
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
	if(buildturn == ((GameScene*)scene)->turnCount){
		createUnit();
	}
}

void TownCenter::enemyTurn() {
	if(allowBuild() && rand()%3 == 0) {
		buildturn = ((GameScene*)scene)->turnCount;
		((GameScene*)scene)->players[player]->useResources(PEASANTCOST);
	}
}

bool TownCenter::allowBuild() {
	Player* player = ((GameScene*)scene)->players[this->player];
	if(!player->hasResources(PEASANTCOST)) {
		return false;
	}

	if(buildturn < ((GameScene*)scene)->turnCount) {
		return true;
	}
	return false;
}