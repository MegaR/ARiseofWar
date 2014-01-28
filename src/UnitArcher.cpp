#include "UnitArcher.h"

#include "Game.h"

#include <iostream>
using namespace std;

UnitArcher::UnitArcher(int _x, int _y, int _player, Scene* scene) : Unit(_x, _y, _player, scene)
{
	maxHP = 9;
	hp = maxHP;
	attack = 4;
	defense = 2;
	maxDistance = 5;
	attackDistance = 3;
	maxModels = 3;
	
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/UnitArcher.md2");
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/UnitArcher.png");
	} else {
		texture = game->videoDriver->getTexture("res/UnitArcherEnemy.png");
	}
	
	for(int i = 0; i < maxModels; i++) {
		addModel();
	}
	uaplayed = false;
}

UnitArcher::~UnitArcher()
{
	Game::getInstance().playSound("res/seDeath.wav", false);
	//uaBGM->drop();
}

void UnitArcher::selected() {
	Unit::selected();
	
	if (Game::getInstance().soundEffectsOn == true)
	{
		if ((player == 0) && !(path.size() > 0))
		{ 
			Game::getInstance().playSound("res/seArcherSelected.wav", false); 
		}
	}
}
  
void UnitArcher::update()
{
	Unit::update();

	if (Game::getInstance().soundEffectsOn == true)
	{
		if ((player == 0) && (path.size() > 0))
		{ 
			if (!uaplayed)
			{
				Game::getInstance().playSound("res/seArcherMove.wav", false);
				uaplayed = true;
			}
		}
	}
}

void UnitArcher::startTurn()
{
	Unit::startTurn();
	uaplayed = false;
}