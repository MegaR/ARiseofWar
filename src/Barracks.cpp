#include "Barracks.h"
#include "Game.h"

Barracks::Barracks(int tileX, int tileY, int player, Scene* scene) : Building(tileX, tileY, player, scene)
{
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/buildingBarracks.3DS");
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/buildingBarracks.png");
	} else {
		texture = game->videoDriver->getTexture("res/buildingBarracksEnemy.png");
	}
	sizeX = 2;
	sizeY = 2;
	createModel();
	node->setScale(vector3df(0.69f,0.69f,0.69f));
	node->setRotation(vector3df(0,30,0));
	GUI = game->gui->addImage(rect<s32>(0,0, 300, 125));
	txt =	game->gui->addStaticText(L"knight duurt 2 beurten om te bouwen" ,rect<s32>(0,0, 300, 100));
	GUI->setVisible(false); 
	txt->setVisible(false);
	buildturn = -1;

	hp = 4;
	defense = 2;

	knightButton = new Button(120, 35, 75, 75, "knight", game->videoDriver->getTexture("res/guiButtonCreate.png") );
	knightButton->btn->setVisible(false);
}


Barracks::~Barracks(void)
{
	GUI->remove();
	txt->remove();
	delete knightButton;
}

void Barracks::update(){
	knightButton->update();
	addtoqueue();
}

void Barracks::createUnit(){
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
		((GameScene*)game->currentScene)->entities.push_back(new UnitKnight(list->at(0).X,list->at(0).Y, player, scene ));
		delete list;
	}
}

void Barracks::addtoqueue(){
	Game* game = &Game::getInstance();
	
	if((game->eventReceiver->isKeyPressed(KEY_KEY_K) || knightButton->pressed) && allowBuild()){
		buildturn = ((GameScene*)scene)->turnCount + KNIGHTBUILDTIME;
		((GameScene*)scene)->players[player]->useResources(KNIGHTCOST);
		knightButton->btn->setEnabled(false);
		cout << "queued Knight" << endl;
	}
}

void Barracks::selected(){
	Game* game = &Game::getInstance();

	if(player != 0) return;
	
	GUI->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
	GUI->setVisible(true);
	txt->setVisible(true);
	knightButton->btn->setVisible(true);
	if(allowBuild()) {
		knightButton->btn->setEnabled(true);
	} else {
		knightButton->btn->setEnabled(false);
	}
}

void Barracks::deselected(){
		GUI->setVisible(false);
		txt->setVisible(false);
		knightButton->btn->setVisible(false);
}

void  Barracks::startTurn(){
	Game* game = &Game::getInstance();
	if(buildturn == ((GameScene*)scene)->turnCount) {
		createUnit();
		cout<< "creating knight" << endl;
	}
}

void Barracks::enemyTurn() {
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;
	if(allowBuild() && rand()%2 == 0) {
		buildturn = scene->turnCount;
	}
}

bool Barracks::allowBuild() {
	Player* player = ((GameScene*)scene)->players[this->player];
	if(!player->hasResources(KNIGHTCOST)) {
		return false;
	}

	if(buildturn < ((GameScene*)scene)->turnCount) {
		return true;
	}
	return false;
}