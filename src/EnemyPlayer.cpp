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
	queue.empty();
	for(int i = 0; i < scene->entities.size(); i++) {
		if(scene->entities[i]->player == 1) {
			queue.push_back(scene->entities[i]);
		}
	}
	current = 0;
	/*
	//todo: sort entities
	for(int i = 0; i < scene->entities.size(); i++) {
		if(scene->entities[i]->player == 1) {
			scene->entities[i]->enemyTurn();
		}
	}
	scene->nextTurn();
	*/
}

void EnemyPlayer::update() {
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;

	if(queue.size() > 0) {

		if(current == 0) {
			current = queue.back();
			queue.pop_back();
			if(current->enemyTurn()) {
				current = 0;
			}
		} else {
			Unit* unit = 0;
			unit = dynamic_cast<Unit*>(current);
			if(unit || unit->currentAnimation == IDLE_ANIMATION) {
				if(unit->currentAnimation == IDLE_ANIMATION) {
					current = 0;
				}
			} else {
				current = 0;
			}
		}
		
	} else {
		scene->nextTurn();
	}
}