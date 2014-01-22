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
	GUI = game->gui->addImage(rect<s32>(0,40, 510, 200));
	GUI->setImage(game->videoDriver->getTexture("res/guiBuildMenu.png"));
	knightTXT = game->gui->addStaticText(L"Het duurt 2 beurten om de Knight te maken.", rect<s32>(10, 135, 170, 195));
	archerTXT = game->gui->addStaticText(L"Het duurt 1 beurt om de Archer te maken.", rect<s32>(180, 135, 340, 195));
	//spearmanTXT = game->gui->addStaticText(L"Het duurt 1 beurt om de Spearman te maken.", rect<s32>(350, 135, 510, 195));
	GUI->setVisible(false); 
	knightTXT->setVisible(false);
	archerTXT->setVisible(false);
	//spearmanTXT->setVisible(false);
	buildturn = -1;

	hp = 4;
	defense = 2;

	knightButton = new Button(10, 50, 75, 75, "Knight", game->videoDriver->getTexture("res/guiButtonCreate.png") );
	knightButton->btn->setVisible(false);
	
	archerButton = new Button(180, 50, 75, 75, "Archer", game->videoDriver->getTexture("res/guiButtonCreate.png") );
	archerButton->btn->setVisible(false);

	//spearmanButton = new Button(350, 50, 75, 75, "Spearman", game->videoDriver->getTexture("res/guiButtonCreate.png") );
	//spearmanButton->btn->setVisible(false);

	creatingUnit = 0; //0 = Nothing, 1 = Knight, 2 = Archer, 3 = Spearman.
}


Barracks::~Barracks(void)
{
	GUI->remove();
	knightTXT->remove();
	archerTXT->remove();
	//spearmanTXT->remove();
	
	delete knightButton;
	delete archerButton;
	//delete spearmanButton;
}

void Barracks::update(){
	knightButton->update();
	archerButton->update();
	//spearmanButton->update();

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
		if (creatingUnit == 1) { ((GameScene*)game->currentScene)->entities.push_back(new UnitKnight(list->at(0).X,list->at(0).Y, player, scene)); }
		else if (creatingUnit == 2) { ((GameScene*)game->currentScene)->entities.push_back(new UnitArcher(list->at(0).X,list->at(0).Y, player, scene)); }
		//else if (creatingUnit == 3) { ((GameScene*)game->currentScene)->entities.push_back(new UnitSpearman(list->at(0).X,list->at(0).Y, player, scene)); }
		else { cout << "No valid unit ID" << endl; }
		delete list;
	}
}

void Barracks::addtoqueue(){
	Game* game = &Game::getInstance();
	
	if((game->eventReceiver->isKeyPressed(KEY_KEY_K) || knightButton->pressed) && allowBuildKnight()){
		buildturn = ((GameScene*)scene)->turnCount + KNIGHTBUILDTIME;
		((GameScene*)scene)->players[player]->useResources(KNIGHTCOST);

		knightButton->btn->setEnabled(false);
		archerButton->btn->setEnabled(false);
		//spearmanButton->btn->setEnabled(false);

		creatingUnit = 1;

		cout << "queued knight" << endl;
	}

	if((game->eventReceiver->isKeyPressed(KEY_KEY_L) || archerButton->pressed) && allowBuildArcher()){
		buildturn = ((GameScene*)scene)->turnCount + ARCHERBUILDTIME;
		((GameScene*)scene)->players[player]->useResources(ARCHERCOST);

		knightButton->btn->setEnabled(false);
		archerButton->btn->setEnabled(false);
		//spearmanButton->btn->setEnabled(false);
		creatingUnit = 2;

		cout << "queued archer" << endl;
	}

	/*if((game->eventReceiver->isKeyPressed(KEY_KEY_J) || spearmanButton->pressed) && allowBuildSpearman()){
		buildturn = ((GameScene*)scene)->turnCount + SPEARMANBUILDTIME;
		((GameScene*)scene)->players[player]->useResources(SPEARMANCOST);

		knightButton->btn->setEnabled(false);
		archerButton->btn->setEnabled(false);
		spearmanButton->btn->setEnabled(false);
		creatingUnit = 3;

		cout << "queued spearman" << endl;
	}*/
}

void Barracks::selected(){
	Game* game = &Game::getInstance();

	if(player != 0) return;
	
	//GUI->setImage(game->videoDriver->getTexture("res/guiBuildMenu.png"));
	GUI->setVisible(true);

	knightTXT->setVisible(true);
	knightButton->btn->setVisible(true);
	if(allowBuildKnight()) { knightButton->btn->setEnabled(true); } 
	else { knightButton->btn->setEnabled(false); }
	
	archerTXT->setVisible(true);
	archerButton->btn->setVisible(true);
	if(allowBuildArcher()) { archerButton->btn->setEnabled(true); } 
	else { archerButton->btn->setEnabled(false); }
	
	/*archerTXT->setVisible(true);
	archerButton->btn->setVisible(true);
	if(allowBuildArcher()) { archerButton->btn->setEnabled(true); } 
	else { archerButton->btn->setEnabled(false); }*/
}

void Barracks::deselected(){
		GUI->setVisible(false);

		knightTXT->setVisible(false);
		archerTXT->setVisible(false);
		//spearmanTXT->setVisible(false);

		knightButton->btn->setVisible(false);
		archerButton->btn->setVisible(false);
		//spearmanButton->btn->setVisible(false);
}

void  Barracks::startTurn(){
	Game* game = &Game::getInstance();
	if(buildturn == ((GameScene*)scene)->turnCount) {
		createUnit();
	}
}

bool Barracks::enemyTurn() {
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;

	if(allowBuildKnight() && rand()%3 == 0) {
		buildturn = scene->turnCount;
	}

	if(allowBuildArcher() && rand()%3 == 0) {
		buildturn = scene->turnCount;
	}

	/*if(allowBuildSpearman() && rand()%3 == 0) {
		buildturn = scene->turnCount;
	}*/
	
	return false;
}

bool Barracks::allowBuildKnight() {
	Player* player = ((GameScene*)scene)->players[this->player];

	if(!player->hasResources(KNIGHTCOST)) {
		return false;
	}

	if(buildturn < ((GameScene*)scene)->turnCount) {
		return true;
	}
	return false;
}

bool Barracks::allowBuildArcher() {
	Player* player = ((GameScene*)scene)->players[this->player];

	if(!player->hasResources(ARCHERCOST)) {
		return false;
	}

	if(buildturn < ((GameScene*)scene)->turnCount) {
		return true;
	}
	return false;
}

/*bool Barracks::allowBuildSpearman() {
	Player* player = ((GameScene*)scene)->players[this->player];

	if(!player->hasResources(SPEARMANCOST)) {
		return false;
	}

	if(buildturn < ((GameScene*)scene)->turnCount) {
		return true;
	}
	return false;
}*/
