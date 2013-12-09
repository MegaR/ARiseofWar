#include "EnemyPlayer.h"
#include "Game.h"

EnemyPlayer::EnemyPlayer(void)
{
}


EnemyPlayer::~EnemyPlayer(void)
{
}

void EnemyPlayer::turn() {
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;
	//todo: sort entities
	for(int i = 0; i < scene->entities.size(); i++) {
		if(scene->entities[i]->player == 1) {
			scene->entities[i]->enemyTurn();
		}
	}
	scene->nextTurn();
}