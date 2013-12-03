#include "UnitKnight.h"

#include "Game.h"

#include <iostream>
using namespace std;

UnitKnight::UnitKnight(int _x, int _y, int _player) : Unit(_x, _y, _player)
{
	hp = 10;
	attack = 4;
	defense = 3;
	maxDistance = 4;
	attackDistance = 1;
	
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("C:/irrlicht-1.8/media/sydney.md2");
	
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