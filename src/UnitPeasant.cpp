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

	GUI = game->gui->addImage(rect<s32>(0, 40, 435, 135));
	GUI->setImage(game->videoDriver->getTexture("res/guiPeasant.png"));
	GUI->setVisible(false);

	buildBarracksButton = new Button(10, 50, 75, 75, "Barracks", "Wood: 10\nFood: 20\nStone: 10\nGold: 10", game->videoDriver->getTexture("res/guiButtonCreate.png"));
	buildBarracksButton->btn->setVisible(false);

	buildLumberMillButton = new Button(95, 50, 75, 75, "Lumber\nMill", "Wood: 30\nFood: 0\nStone: 10\nGold: 10", game->videoDriver->getTexture("res/guiButtonCreate.png"));
	buildLumberMillButton->btn->setVisible(false);

	buildQuarryButton = new Button(180, 50, 75, 75, "Quarry", "Wood: 0\nFood: 0\nStone: 20\nGold: 30", game->videoDriver->getTexture("res/guiButtonCreate.png"));
	buildQuarryButton->btn->setVisible(false);

	buildFarmButton = new Button(265, 50, 75, 75, "Farm", "Wood: 0\nFood: 30\nStone: 5\nGold: 15", game->videoDriver->getTexture("res/guiButtonCreate.png"));
	buildFarmButton->btn->setVisible(false);

	buildSiegeWorkshopButton = new  Button(350, 50, 75, 75, "Siege\nWorkshop", "Wood: 25\nFood: 0\nStone: 15\nGold: 10", game->videoDriver->getTexture("res/guiButtonCreate.png"));
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
	if(resourceBuilding()) {
		return true;
	}

	if(!hasMoved) {
		gotoClearing();
	}

	if(reasonableSpace(tileX, tileY) ) {
		cout << "BR ratio: " << barracksSiegeRatio() << endl;
		if(barracksSiegeRatio() < BARRACKSSIEGERATIO) {
			if(attemptBuildBarracks()) return true;
		} else {
			if(attemptBuildSiegeWorkshop()) return true;
		}
	}

	return false;
}

bool UnitPeasant::resourceBuilding() {
	Player* player = ((GameScene*)scene)->players[1];
	vector2d<int> dest;

	if(!player->hasResources(0, MINFOOD, 0, 0)) {
		cout << "need food" << endl;
		if(player->hasResources(FARMCOST) ) {
			dest = findWheat();
			cout << "X: " << dest.X << " Y: " << dest.Y << endl;
			if(dest != vector2d<int>(-1,-1) ) {
				moveTo(dest.X+1, dest.Y);
				if(attemptBuildFarm()) {
					return true;
				}
				moveTo(dest.X-1, dest.Y);
				if(attemptBuildFarm()) {
					return true;
				}
				moveTo(dest.X, dest.Y+1);
				if(attemptBuildFarm()) {
					return true;
				}
				moveTo(dest.X, dest.Y-1);
				if(attemptBuildFarm()) {
					return true;
				}
			}
		} else {
			cout << "not enough resources for farm" << endl;
		}
	}

	if(!player->hasResources(MINWOOD, 0, 0, 0)) {
		cout << "need wood" << endl;
		if(player->hasResources(LUMBERMILLCOST) ) {
			dest = findForest();
			cout << "X: " << dest.X << " Y: " << dest.Y << endl;
			if(dest != vector2d<int>(-1,-1) ) {
				moveTo(dest.X+1, dest.Y);
				if(attemptBuildLumberMill()) {
					return true;
				}
				moveTo(dest.X-1, dest.Y);
				if(attemptBuildLumberMill()) {
					return true;
				}
				moveTo(dest.X, dest.Y+1);
				if(attemptBuildLumberMill()) {
					return true;
				}
				moveTo(dest.X, dest.Y-1);
				if(attemptBuildLumberMill()) {
					return true;
				}
			}
		} else {
			cout << "not enough resources for lumbermill" << endl;
		}
	}

	if(!player->hasResources(0, 0, MINSTONE, MINGOLD)) {
		cout << "need stone/gold" << endl;
		if(player->hasResources(QUARRYCOST) ) {
			dest = findStone();
			cout << "X: " << dest.X << " Y: " << dest.Y << endl;
			if(dest != vector2d<int>(-1,-1) ) {
				moveTo(dest.X+1, dest.Y);
				if(attemptBuildQuarry()) {
					return true;
				}
				moveTo(dest.X-1, dest.Y);
				if(attemptBuildQuarry()) {
					return true;
				}
				moveTo(dest.X, dest.Y+1);
				if(attemptBuildQuarry()) {
					return true;
				}
				moveTo(dest.X, dest.Y-1);
				if(attemptBuildQuarry()) {
					return true;
				}
			}
		} else {
			cout << "not enough resources for quarry" << endl;
		}
	}

	return false;
}

vector2d<int> UnitPeasant::findWheat() {
	GameScene* gameScene = (GameScene*) scene; 
	//growing cube check for resource
	for(int size = 1; size < MAPSIZE; size++) {
		
		for(int x = -size; x < size; x += size*2) {
			for(int y = -size; y < size; y++) {
				if(tileX + x >= MAPSIZE || tileX + x < 0 || tileY + y >= MAPSIZE || tileY + y < 0) continue;

				TileWheat* tile;
				tile = dynamic_cast<TileWheat*>(gameScene->tilesystem.tiles[tileX+x][tileY+y]);
				if(tile) return vector2d<int>(tileX+x, tileY+y);
			}
		}

		for(int y = -size; y < size; y += size*2) {
			for(int x = -size; x < size; x++) {
				if(tileX + x >= MAPSIZE || tileX + x < 0 || tileY + y >= MAPSIZE || tileY + y < 0) continue;

				TileWheat* tile;
				tile = dynamic_cast<TileWheat*>(gameScene->tilesystem.tiles[tileX+x][tileY+y]);
				if(tile) return vector2d<int>(tileX+x, tileY+y);
			}
		}
	}
	return vector2d<int>(-1,-1);
}

vector2d<int> UnitPeasant::findStone() {
	GameScene* gameScene = (GameScene*) scene; 
	//growing cube check for resource
	for(int size = 1; size < MAPSIZE; size++) {
		
		for(int x = -size; x < size; x += size*2) {
			for(int y = -size; y < size; y++) {
				if(tileX + x >= MAPSIZE || tileX + x < 0 || tileY + y >= MAPSIZE || tileY + y < 0) continue;

				TileRocks* tile;
				tile = dynamic_cast<TileRocks*>(gameScene->tilesystem.tiles[tileX+x][tileY+y]);
				if(tile) return vector2d<int>(tileX+x, tileY+y);
			}
		}

		for(int y = -size; y < size; y += size*2) {
			for(int x = -size; x < size; x++) {
				if(tileX + x >= MAPSIZE || tileX + x < 0 || tileY + y >= MAPSIZE || tileY + y < 0) continue;

				TileRocks* tile;
				tile = dynamic_cast<TileRocks*>(gameScene->tilesystem.tiles[tileX+x][tileY+y]);
				if(tile) return vector2d<int>(tileX+x, tileY+y);
			}
		}
	}
	return vector2d<int>(-1,-1);
}

vector2d<int> UnitPeasant::findForest() {
	GameScene* gameScene = (GameScene*) scene; 
	//growing cube check for resource
	for(int size = 1; size < MAPSIZE; size++) {
		
		for(int x = -size; x < size; x += size*2) {
			for(int y = -size; y < size; y++) {
				if(tileX + x >= MAPSIZE || tileX + x < 0 || tileY + y >= MAPSIZE || tileY + y < 0) continue;

				TileForest* tile;
				tile = dynamic_cast<TileForest*>(gameScene->tilesystem.tiles[tileX+x][tileY+y]);
				if(tile) return vector2d<int>(tileX+x, tileY+y);
			}
		}

		for(int y = -size; y < size; y += size*2) {
			for(int x = -size; x < size; x++) {
				if(tileX + x >= MAPSIZE || tileX + x < 0 || tileY + y >= MAPSIZE || tileY + y < 0) continue;

				TileForest* tile;
				tile = dynamic_cast<TileForest*>(gameScene->tilesystem.tiles[tileX+x][tileY+y]);
				if(tile) return vector2d<int>(tileX+x, tileY+y);
			}
		}
	}
	return vector2d<int>(-1,-1);
}

void UnitPeasant::gotoClearing() {
	GameScene* gameScene = (GameScene*) scene;

	for(int size = 1; size < MAPSIZE; size++) {
		
		for(int x = -size; x < size; x += size*2) {
			for(int y = -size; y < size; y++) {
				if(tileX + x >= MAPSIZE || tileX + x < 0 || tileY + y >= MAPSIZE || tileY + y < 0) continue;

				if(reasonableSpace(tileX+x, tileY+y)) {
						cout << "found clearing X: " << tileX+x << " Y: " << tileY + y << endl;
						moveTo(tileX+x, tileY+y);
						return;
				}
			}
		}

		for(int y = -size; y < size; y += size*2) {
			for(int x = -size; x < size; x++) {
				if(tileX + x >= MAPSIZE || tileX + x < 0 || tileY + y >= MAPSIZE || tileY + y < 0) continue;

				if(reasonableSpace(tileX+x, tileY+y)) {
						cout << "found clearing X: " << tileX+x << " Y: " << tileY + y << endl;
						moveTo(tileX+x, tileY+y);
						return;
				}
			}
		}
	}
}

bool UnitPeasant::reasonableSpace(int tileX, int tileY) {
	GameScene* scene = (GameScene*)this->scene;

	for(int x = -1; x < 3; x++) {
		for(int y = -1; y < 3; y++) {
			if(tileX + x >= MAPSIZE || tileX + x < 0 || tileY + y >= MAPSIZE || tileY + y < 0) return false;
			Tile* tile = scene->tilesystem.tiles[tileX+x][tileY+y];
			if(!tile->walkable || (tile->getEntity() && tile->getEntity() != this) ) {
				return false;
			}
		}
	}

	return true;
}

float UnitPeasant::barracksSiegeRatio() {
	GameScene* scene = (GameScene*)this->scene;
	float barracks = 0;
	float sieges = 0;
	for(int i = 0; i < scene->entities.size(); i++) {
		Barracks* barrack;
		SiegeWorkshop* siege;

		barrack = dynamic_cast<Barracks*>(scene->entities[i]);
		if(barrack && barrack->player == player) {
			barracks++;
			continue;
		}

		siege = dynamic_cast<SiegeWorkshop*>(scene->entities[i]);
		if(siege && siege->player == player) {
			sieges++;
		}
	}

	if(sieges == 0) return barracks;
	return barracks / sieges;
}