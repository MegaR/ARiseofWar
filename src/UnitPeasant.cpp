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
	
	for(int i = 0; i < maxModels; i++) {
		addModel();
	}
}


UnitPeasant::~UnitPeasant()
{
}
