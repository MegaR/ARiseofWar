#include "UnitKnight.h"

#include "Game.h"

#include <iostream>
using namespace std;

UnitKnight::UnitKnight(int _x, int _y, int _player) : Unit(_x, _y, _player)
{
	hp = 5;
	attack = 5;
	defense = 3;
	maxDistance = 4;
	attackDistance = 1;
	
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/unitKnight.md2");
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/unitKnight.png");
	} else {
		texture = game->videoDriver->getTexture("res/unitKnightEnemy.png");
	}
	
	addModel();
	addModel();
	addModel();
	addModel();
	addModel();
}

UnitKnight::~UnitKnight()
{
}