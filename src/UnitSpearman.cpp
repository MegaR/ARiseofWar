#include "UnitSpearman.h"

#include "Game.h"

#include <iostream>
using namespace std;

UnitSpearman::UnitSpearman(int _x, int _y, int _player, Scene* scene) : Unit(_x, _y, _player, scene)
{
	maxHP = 10;
	hp = maxHP;
	attack = 5;
	defense = 3;
	maxDistance = 4;
	attackDistance = 2;
	maxModels = 5;
	
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/UnitSpearman.md2");
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/UnitSpearman.png");
	} else {
		texture = game->videoDriver->getTexture("res/UnitSpearmanEnemy.png");
	}
	
	for(int i = 0; i < maxModels; i++) {
		addModel();
	}

	usplayed = false;
}

UnitSpearman::~UnitSpearman()
{
	Game::getInstance().playSound("res/seDeath.wav", false);
}

void UnitSpearman::selected() {
	Unit::selected();
	
	if (Game::getInstance().soundEffectsOn == true)
	{
		if ((player == 0) && !(path.size() > 0))
		{ 
			Game::getInstance().playSound("res/seSpearmanSelected.wav", false); 
		}
	}
}
  
void UnitSpearman::update()
{
	Unit::update();

	if (Game::getInstance().soundEffectsOn == true)
	{
		if ((player == 0) && (path.size() > 0))
		{ 
			if (!usplayed)
			{
				Game::getInstance().playSound("res/seSpearmanMove.wav", false);
				usplayed = true;
			}
		}
	}
}

void UnitSpearman::startTurn()
{
	Unit::startTurn();
	usplayed = false;
}