#include "UnitKnight.h"

#include "Game.h"

#include <iostream>
using namespace std;

ISoundEngine* ukBGM;
bool ukplayed;

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

	ukBGM = createIrrKlangDevice();
	ukplayed = false;
}

UnitKnight::~UnitKnight()
{
	//ukBGM->drop();
}

void UnitKnight::selected() {
	Unit::selected();
	if (Game::getInstance().soundEffectsOn == true)
	{
		if ((player == 0) && !(path.size() > 0))
		{ 
			ukBGM->play2D("res/seKnightSelected.wav", false); 
		}
	}
}

void UnitKnight::update()
{
	Unit::update();

	if (Game::getInstance().soundEffectsOn == true)
	{
		if ((player == 0) && (path.size() > 0))
		{ 
			if (!ukplayed)
			{
				ukBGM->play2D("res/seKnightMove.wav", false);
				ukplayed = true;
			}
		}
	}
}

void UnitKnight::startTurn()
{
	Unit::startTurn();
	ukplayed = false;
}