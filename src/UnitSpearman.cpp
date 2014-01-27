#include "UnitSpearman.h"

#include "Game.h"

#include <iostream>
using namespace std;

ISoundEngine* usBGM;
bool usplayed;

UnitSpearman::UnitSpearman(int _x, int _y, int _player, Scene* scene) : Unit(_x, _y, _player, scene)
{
	maxHP = 9;
	hp = maxHP;
	attack = 4;
	defense = 2;
	maxDistance = 5;
	attackDistance = 3;
	maxModels = 3;
	
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

	usBGM = createIrrKlangDevice();
	usplayed = false;
}

UnitSpearman::~UnitSpearman()
{
	usBGM->play2D("res/seDeath.wav", false);
	//usBGM->drop();
}

void UnitSpearman::selected() {
	Unit::selected();
	
	if (Game::getInstance().soundEffectsOn == true)
	{
		if ((player == 0) && !(path.size() > 0))
		{ 
			usBGM->play2D("res/seSpearmanSelected.wav", false); 
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
				usBGM->play2D("res/seSpearmanMove.wav", false);
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