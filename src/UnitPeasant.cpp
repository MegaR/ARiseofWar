#include "UnitPeasant.h"
#include "Game.h"

#include <iostream>
using namespace std;

UnitPeasant::UnitPeasant(int _x, int _y, int _player) : Unit(_x, _y, _player)
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
	
	showGUI = false;
	isSelected = false;
	buildingBuilt = false;

	GUI = game->gui->addImage(rect<s32>(0,40, 95, 135));
	GUI->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
	GUI->setVisible(false);

	buildBarracksButton = new Button(10, 50, 75, 75, "Barracks", game->videoDriver->getTexture("res/guiButtonCreate.png"));
	buildBarracksButton->btn->setVisible(false);

	for(int i = 0; i < maxModels; i++) {
		addModel();
	}
}


UnitPeasant::~UnitPeasant()
{
	delete buildBarracksButton;
	GUI->remove();
}

void UnitPeasant::update()
{
	Unit::update();
	buildBarracksButton->update();

	GUI->setVisible(showGUI);
	buildBarracksButton->btn->setVisible(showGUI);

	if((isSelected == false) && (buildingBuilt == true))
	{
		showGUI = false;
	}

	GameScene* scene = (GameScene*)Game::getInstance().currentScene;
	if(scene->nextTurnButton->pressed)
	{
		showGUI = false;
		isSelected = false;
		buildingBuilt = false;
	}

	if (buildBarracksButton->pressed)
	{
		attemptBuildBarracks();
	}	
}

bool UnitPeasant::attemptBuildBarracks() {
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;
	buildingBuilt = true;
	TileGrass* validTile2 = dynamic_cast<TileGrass*>(scene->tilesystem.tiles[tileX+1][tileY]);
	TileGrass* validTile3 = dynamic_cast<TileGrass*>(scene->tilesystem.tiles[tileX][tileY+1]);
	TileGrass* validTile4 = dynamic_cast<TileGrass*>(scene->tilesystem.tiles[tileX+1][tileY+1]);

	if((scene->getEntity(tileX+1, tileY)) || (scene->getEntity(tileX, tileY+1)) || (scene->getEntity(tileX+1, tileY+1)) || (!validTile2) || (!validTile3) || (!validTile4))
	{
		return false;
	} else {
		scene->entities.push_back(new Barracks(tileX, tileY, player));
		scene->removeEntity(this);
		return true;
	}
}

void UnitPeasant::selected()
{
	Unit::selected();
	showGUI = true;
	isSelected = true;
}

void UnitPeasant::deselected()
{
	Unit::deselected();
	isSelected = false;
	showGUI = false;
}

void UnitPeasant::enemyTurn() {
	if(reasonableSpace()) {
		if(attemptBuildBarracks()) {
			return;
		}
	}

	int destX = rand() % MAPSIZE;
	int destY = rand() % MAPSIZE;

	this->moveTo(destX, destY);

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
