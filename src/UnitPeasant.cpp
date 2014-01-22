#include "UnitPeasant.h"
#include "Game.h"

#include <iostream>
using namespace std;

UnitPeasant::UnitPeasant(int _x, int _y, int _player, Scene* scene) : Unit(_x, _y, _player, scene)
{
	hp = 1;
	maxHP = 1;
	maxModels = 1;
	attack = 2;
	defense = 1;
	maxDistance = 7;
	attackDistance = 1;
	
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/unitPeasant.md2");
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/unitPeasant.png");
	} else {
		texture = game->videoDriver->getTexture("res/unitPeasantEnemy.png");
	}

	GUI = game->gui->addImage(rect<s32>(0,40, 335, 135));
	GUI->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
	GUI->setVisible(false);

	buildBarracksButton = new Button(10, 50, 75, 75, "Barracks", game->videoDriver->getTexture("res/guiButtonCreate.png"));
	buildBarracksButton->btn->setVisible(false);
	buildLumberMillButton = new Button(90, 50, 75, 75, "Lumber\nMill", game->videoDriver->getTexture("res/guiButtonCreate.png"));
	buildLumberMillButton->btn->setVisible(false);
	buildQuarryButton = new Button(170, 50, 75, 75, "Quarry", game->videoDriver->getTexture("res/guiButtonCreate.png"));
	buildQuarryButton->btn->setVisible(false);
	buildFarmButton = new Button(250, 50, 75, 75, "Farm", game->videoDriver->getTexture("res/guiButtonCreate.png"));
	buildFarmButton->btn->setVisible(false);
	buildSiegeWorkshopButton = new  Button(290, 50, 75, 75, "SiegeWorkshop", game->videoDriver->getTexture("res/guiButtonCreate.png"));
	buildSiegeWorkshopButton->btn->setVisible(false);

	for(int i = 0; i < maxModels; i++) {
		addModel();
	}
}


UnitPeasant::~UnitPeasant() {
	delete buildLumberMillButton;
	delete buildBarracksButton;
	delete buildQuarryButton;
	delete buildFarmButton;
	delete buildSiegeWorkshopButton;
	GUI->remove();
}

void UnitPeasant::update() {
	Unit::update();
	buildBarracksButton->update();
	buildLumberMillButton->update();
	buildQuarryButton->update();
	buildFarmButton->update();
	buildSiegeWorkshopButton->update();

	GameScene* scene = (GameScene*)Game::getInstance().currentScene;

	if (buildBarracksButton->pressed)
	{
		if(attemptBuildBarracks())
			return;
	}

	if (buildLumberMillButton->pressed) {
		if(attemptBuildLumberMill())
			return;
	}

	if(buildQuarryButton->pressed) {
		if(attemptBuildQuarry())
			return;
	}

	if(buildFarmButton->pressed) {
		if(attemptBuildFarm())
			return;
	}

	if(buildSiegeWorkshopButton->pressed){
		if(attemptBuildSiegeWorkshop())
			return;
	}
}

bool UnitPeasant::attemptBuildBarracks() {
	if(tileX <=0 || tileY >= MAPSIZE-1) return false;
	GameScene* scene = (GameScene*)this->scene;
	if(!scene->players[player]->hasResources(BARRACKSCOST)) {
		return false;
	}

	TileGrass* validTile2 = dynamic_cast<TileGrass*>(scene->tilesystem.tiles[tileX+1][tileY]);
	TileGrass* validTile3 = dynamic_cast<TileGrass*>(scene->tilesystem.tiles[tileX][tileY+1]);
	TileGrass* validTile4 = dynamic_cast<TileGrass*>(scene->tilesystem.tiles[tileX+1][tileY+1]);

	if((scene->getEntity(tileX+1, tileY)) || (scene->getEntity(tileX, tileY+1)) || (scene->getEntity(tileX+1, tileY+1)) || (!validTile2) || (!validTile3) || (!validTile4))
	{
		return false;
	} else {
		scene->entities.push_back(new Barracks(tileX, tileY, player, scene));
		scene->players[player]->useResources(BARRACKSCOST);
		scene->removeEntity(this);
		return true;
	}
}

bool UnitPeasant::attemptBuildLumberMill() {
	GameScene* scene = (GameScene*)this->scene;
	if(!scene->players[player]->hasResources(LUMBERMILLCOST)) {
		return false;
	}

	TileForest* tile;
	tile = dynamic_cast<TileForest*>(scene->tilesystem.tiles[tileX+1][tileY]);
	if(tile != NULL) {buildLumberMill(tileX+1, tileY); return true;}
	tile = dynamic_cast<TileForest*>(scene->tilesystem.tiles[tileX-1][tileY]);
	if(tile != NULL) {buildLumberMill(tileX-1, tileY); return true;}
	tile = dynamic_cast<TileForest*>(scene->tilesystem.tiles[tileX][tileY+1]);
	if(tile != NULL) {buildLumberMill(tileX, tileY+1); return true;}
	tile = dynamic_cast<TileForest*>(scene->tilesystem.tiles[tileX][tileY-1]);
	if(tile != NULL) {buildLumberMill(tileX, tileY-1); return true;}
	tile = dynamic_cast<TileForest*>(scene->tilesystem.tiles[tileX+1][tileY+1]);
	if(tile != NULL) {buildLumberMill(tileX+1, tileY+1); return true;}
	tile = dynamic_cast<TileForest*>(scene->tilesystem.tiles[tileX+1][tileY-1]);
	if(tile != NULL) {buildLumberMill(tileX+1, tileY-1); return true;}
	tile = dynamic_cast<TileForest*>(scene->tilesystem.tiles[tileX-1][tileY+1]);
	if(tile != NULL) {buildLumberMill(tileX-1, tileY+1); return true;}
	tile = dynamic_cast<TileForest*>(scene->tilesystem.tiles[tileX-1][tileY-1]);
	if(tile != NULL) {buildLumberMill(tileX-1, tileY-1); return true;}

	return false;
}

void UnitPeasant::buildLumberMill(int tileX, int tileY) {
	delete ((GameScene*)scene)->tilesystem.tiles[tileX][tileY];
	((GameScene*)scene)->tilesystem.tiles[tileX][tileY] = new TileGrass(tileX, tileY);
	((GameScene*)scene)->entities.push_back(new LumberMill(tileX, tileY, player, scene));
	((GameScene*)scene)->players[player]->useResources(LUMBERMILLCOST);
	((GameScene*)scene)->removeEntity(this);
}

bool UnitPeasant::attemptBuildQuarry() {
	GameScene* scene = (GameScene*)this->scene;
	if(!scene->players[player]->hasResources(QUARRYCOST)) {
		return false;
	}

	TileRocks* tile;
	tile = dynamic_cast<TileRocks*>(scene->tilesystem.tiles[tileX+1][tileY]);
	if(tile != NULL) {buildQuarry(tileX+1, tileY); return true;}
	tile = dynamic_cast<TileRocks*>(scene->tilesystem.tiles[tileX-1][tileY]);
	if(tile != NULL) {buildQuarry(tileX-1, tileY); return true;}
	tile = dynamic_cast<TileRocks*>(scene->tilesystem.tiles[tileX][tileY+1]);
	if(tile != NULL) {buildQuarry(tileX, tileY+1); return true;}
	tile = dynamic_cast<TileRocks*>(scene->tilesystem.tiles[tileX][tileY-1]);
	if(tile != NULL) {buildQuarry(tileX, tileY-1); return true;}
	tile = dynamic_cast<TileRocks*>(scene->tilesystem.tiles[tileX+1][tileY+1]);
	if(tile != NULL) {buildQuarry(tileX+1, tileY+1); return true;}
	tile = dynamic_cast<TileRocks*>(scene->tilesystem.tiles[tileX+1][tileY-1]);
	if(tile != NULL) {buildQuarry(tileX+1, tileY-1); return true;}
	tile = dynamic_cast<TileRocks*>(scene->tilesystem.tiles[tileX-1][tileY+1]);
	if(tile != NULL) {buildQuarry(tileX-1, tileY+1); return true;}
	tile = dynamic_cast<TileRocks*>(scene->tilesystem.tiles[tileX-1][tileY-1]);
	if(tile != NULL) {buildQuarry(tileX-1, tileY-1); return true;}

	return false;
}

void UnitPeasant::buildQuarry(int tileX, int tileY) {
	delete ((GameScene*)scene)->tilesystem.tiles[tileX][tileY];
	((GameScene*)scene)->tilesystem.tiles[tileX][tileY] = new TileGrass(tileX, tileY);
	((GameScene*)scene)->entities.push_back(new Quarry(tileX, tileY, player, scene));
	((GameScene*)scene)->players[player]->useResources(QUARRYCOST);
	((GameScene*)scene)->removeEntity(this);
}

bool UnitPeasant::attemptBuildFarm() {
	GameScene* scene = (GameScene*)this->scene;
	if(!scene->players[player]->hasResources(QUARRYCOST)) {
		return false;
	}

	TileWheat* tile;
	tile = dynamic_cast<TileWheat*>(scene->tilesystem.tiles[tileX+1][tileY]);
	if(tile != NULL) {buildFarm(tileX+1, tileY); return true;}
	tile = dynamic_cast<TileWheat*>(scene->tilesystem.tiles[tileX-1][tileY]);
	if(tile != NULL) {buildFarm(tileX-1, tileY); return true;}
	tile = dynamic_cast<TileWheat*>(scene->tilesystem.tiles[tileX][tileY+1]);
	if(tile != NULL) {buildFarm(tileX, tileY+1); return true;}
	tile = dynamic_cast<TileWheat*>(scene->tilesystem.tiles[tileX][tileY-1]);
	if(tile != NULL) {buildFarm(tileX, tileY-1); return true;}
	tile = dynamic_cast<TileWheat*>(scene->tilesystem.tiles[tileX+1][tileY+1]);
	if(tile != NULL) {buildFarm(tileX+1, tileY+1); return true;}
	tile = dynamic_cast<TileWheat*>(scene->tilesystem.tiles[tileX+1][tileY-1]);
	if(tile != NULL) {buildFarm(tileX+1, tileY-1); return true;}
	tile = dynamic_cast<TileWheat*>(scene->tilesystem.tiles[tileX-1][tileY+1]);
	if(tile != NULL) {buildFarm(tileX-1, tileY+1); return true;}
	tile = dynamic_cast<TileWheat*>(scene->tilesystem.tiles[tileX-1][tileY-1]);
	if(tile != NULL) {buildFarm(tileX-1, tileY-1); return true;}

	return false;
}

void UnitPeasant::buildFarm(int tileX, int tileY) {
	delete ((GameScene*)scene)->tilesystem.tiles[tileX][tileY];
	((GameScene*)scene)->tilesystem.tiles[tileX][tileY] = new TileGrass(tileX, tileY);
	((GameScene*)scene)->entities.push_back(new Farm(tileX, tileY, player, scene));
	((GameScene*)scene)->players[player]->useResources(FARMCOST);
	((GameScene*)scene)->removeEntity(this);
}

bool UnitPeasant::attemptBuildSiegeWorkshop(){
	GameScene* scene = (GameScene*)this->scene;
	if(!scene->players[player]->hasResources(SIEGEWORKSHOPCOST)) {
		return false;
	}
	buildSiegeWorkshop(tileX,tileY);
	return true;
}

void UnitPeasant::buildSiegeWorkshop(int tileX, int tileY){
	((GameScene*)scene)->entities.push_back(new SiegeWorkshop(tileX, tileY, player, scene));
	((GameScene*)scene)->players[player]->useResources(SIEGEWORKSHOPCOST);
	((GameScene*)scene)->removeEntity(this);
}

void UnitPeasant::selected() {
	Unit::selected();
	GUI->setVisible(true);
	buildBarracksButton->btn->setVisible(true);
	buildLumberMillButton->btn->setVisible(true);
	buildQuarryButton->btn->setVisible(true);
	buildFarmButton->btn->setVisible(true);
	buildSiegeWorkshopButton->btn->setVisible(true);
	if( ((GameScene*)scene)->players[player]->hasResources(BARRACKSCOST) ) {
		buildBarracksButton->btn->setEnabled(true);
	} else {
		buildBarracksButton->btn->setEnabled(false);
	}
	if( ((GameScene*)scene)->players[player]->hasResources(LUMBERMILLCOST) ) {
		buildLumberMillButton->btn->setEnabled(true);
	} else {
		buildLumberMillButton->btn->setEnabled(false);
	}
	if( ((GameScene*)scene)->players[player]->hasResources(QUARRYCOST) ) {
		buildQuarryButton->btn->setEnabled(true);
	} else {
		buildQuarryButton->btn->setEnabled(false);
	}
	if( ((GameScene*)scene)->players[player]->hasResources(FARMCOST) ) {
		buildFarmButton->btn->setEnabled(true);
	} else {
		buildFarmButton->btn->setEnabled(false);
	}

	if( ((GameScene*)scene)->players[player]->hasResources(SIEGEWORKSHOPCOST) ) {
		buildSiegeWorkshopButton->btn->setEnabled(true);
	} else {
		buildSiegeWorkshopButton->btn->setEnabled(false);
	}
}

void UnitPeasant::deselected() {
	Unit::deselected();
	GUI->setVisible(false);
	buildBarracksButton->btn->setVisible(false);
	buildLumberMillButton->btn->setVisible(false);
	buildQuarryButton->btn->setVisible(false);
	buildFarmButton->btn->setVisible(false);
	buildSiegeWorkshopButton->btn->setVisible(false);
}

bool UnitPeasant::enemyTurn() {
	if(reasonableSpace()) {
		if(attemptBuildBarracks()) {
			return true;
		}
	}

	int destX = rand() % MAPSIZE;
	int destY = rand() % MAPSIZE;

	this->moveTo(destX, destY);
	return false;
}

bool UnitPeasant::reasonableSpace() {
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;
	bool reasonable = true;

	for(int i = 0; i < scene->entities.size(); i++) {
		Building* building = dynamic_cast<Building*>(scene->entities.at(i) );
		if(building) {
			if(building->inAttackRange(tileX, tileY, 5)) {
				reasonable = false;
			}
		}
	}

	return reasonable;
}
