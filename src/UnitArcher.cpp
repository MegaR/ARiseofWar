#include "UnitArcher.h"

#include "Game.h"

#include <iostream>
using namespace std;

UnitArcher::UnitArcher(int _x, int _y, int _player, Scene* scene) : Unit(_x, _y, _player, scene)
{
	maxHP = 9;
	hp = 9;
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
}

UnitArcher::~UnitArcher()
{
}