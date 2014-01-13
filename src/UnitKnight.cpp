#include "UnitKnight.h"

#include "Game.h"

#include <iostream>
using namespace std;

UnitKnight::UnitKnight(int _x, int _y, int _player, Scene* scene) : Unit(_x, _y, _player, scene)
{
	maxHP = 10;
	hp = 10;
	attack = 5;
	defense = 3;
	maxDistance = 4;
	attackDistance = 1;
	maxModels = 5;
	
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/unitKnight.md2");
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/unitKnight.png");
	} else {
		texture = game->videoDriver->getTexture("res/unitKnightEnemy.png");
	}
	
	for(int i = 0; i < maxModels; i++) {
		addModel();
	}
}

UnitKnight::~UnitKnight()
{
}