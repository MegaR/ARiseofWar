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
	model = game->sceneManager->getMesh("res/knightdesu.3ds");
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/knight.png");
	} else {
		texture = game->videoDriver->getTexture("res/knightEnemy.png");
	}
	
	addModel();
	addModel();
	addModel();
	addModel();
	addModel();
}

UnitKnight::~UnitKnight()
{
	cout << "destroyed Knight" << endl;
}