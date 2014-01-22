#include "UnitCatapult.h"

#include "Game.h"

#include <iostream>
using namespace std;

UnitCatapult::UnitCatapult(int _x, int _y, int _player, Scene* scene)  : Unit(_x, _y, _player, scene)
{	
	maxHP = 20;
	hp = 20;
	attack = 8;
	defense = 3;
	maxDistance = 3;
	attackDistance = 2;
	maxModels = 1;
	
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/unitCatapult.md2");
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/unitCatapult.png");
	} else {
		texture = game->videoDriver->getTexture("res/unitCatapultEnemy.png");
	}
	
	for(int i = 0; i < maxModels; i++) {
		addModel();
	}
}


UnitCatapult::~UnitCatapult(void)
{
}
