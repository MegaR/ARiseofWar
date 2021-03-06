#include "SiegeWorkshop.h"
#include "Game.h"


SiegeWorkshop::SiegeWorkshop(int tileX, int tileY, int player, Scene* scene) : Building(tileX, tileY, player, scene)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/Siegeworkshop.md2");
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/Siegeworkshop.png");
	} else {
		texture = game->videoDriver->getTexture("res/SiegeworkshopEnemy.png");
	}
	sizeX = 2;
	sizeY = 2;
	createModel();
	node->setScale(vector3df(1.75f, 1.75f, 1.75f));
	node->setRotation(vector3df(0,30,0));
	GUI = game->gui->addImage(rect<s32>(0,40, 300, 165));
	txt =	game->gui->addStaticText(L"Het duurt 3 beurten om de Catapult te maken." ,rect<s32>(0,40, 300, 140));
	GUI->setVisible(false); 
	txt->setVisible(false);
	buildturn = -1;

	hp = 5;
	defense = 2;

	CatapultButton = new Button(120, 75, 75, 75, "Catapult", "Wood: 20\nFood: 0\nStone: 10\nGold: 0", game->videoDriver->getTexture("res/guiButtonCreate.png") );
	CatapultButton->btn->setVisible(false);
}


SiegeWorkshop::~SiegeWorkshop(void)
{
	GUI->remove();
	txt->remove();
	delete CatapultButton;
}

void SiegeWorkshop::update(){
	CatapultButton->update();
	addtoqueue();
}

void SiegeWorkshop::createUnit(){
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
		((GameScene*)game->currentScene)->entities.push_back(new UnitCatapult(list->at(0).X,list->at(0).Y, player, scene ));
		delete list;
	}
}

void SiegeWorkshop::addtoqueue(){
	Game* game = &Game::getInstance();
	
	if((game->eventReceiver->isKeyPressed(KEY_KEY_C) || CatapultButton->pressed) && allowBuild()){
		buildturn = ((GameScene*)scene)->turnCount + CATAPULTBUILDTIME;
		((GameScene*)scene)->players[player]->useResources(CATAPULTCOST);
		CatapultButton->btn->setEnabled(false);
		cout << "queued Catapult" << endl;
	}
}

void SiegeWorkshop::selected(){
	Game* game = &Game::getInstance();

	if(player != 0) return;
	
	GUI->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
	GUI->setVisible(true);
	txt->setVisible(true);
	CatapultButton->btn->setVisible(true);
	if(allowBuild()) {
		CatapultButton->btn->setEnabled(true);
	} else {
		CatapultButton->btn->setEnabled(false);
	}
}

void SiegeWorkshop::deselected(){
		GUI->setVisible(false);
		txt->setVisible(false);
		CatapultButton->btn->setVisible(false);
}

void  SiegeWorkshop::startTurn(){
	Game* game = &Game::getInstance();
	if(buildturn != -1 && buildturn <= ((GameScene*)scene)->turnCount) {
		createUnit();
		buildturn = -1;
		cout<< "creating Catapult" << endl;
	}
}

bool SiegeWorkshop::enemyTurn() {
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;
	if(allowBuild()) {
		buildturn = scene->turnCount + CATAPULTBUILDTIME;
	}
	return false;
}

bool SiegeWorkshop::allowBuild() {
	Player* player = ((GameScene*)scene)->players[this->player];
	if(!player->hasResources(CATAPULTCOST)) {
		return false;
	}

	if(buildturn < ((GameScene*)scene)->turnCount) {
		return true;
	}
	return false;
}

