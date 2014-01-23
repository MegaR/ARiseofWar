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
			insertToQueue(scene->entities[i]);
		}
	}
	current = 0;
}

void EnemyPlayer::insertToQueue(Entity* entity) {
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;

	if( dynamic_cast<MOVE1*>(entity) ) {
		queue.insert(queue.begin(), entity);

	} else if( dynamic_cast<MOVE2*>(entity) ) {
		for(int i = 0; i < queue.size(); i++) {
			if( !dynamic_cast<MOVE1*>(queue[i]) ) {
				queue.insert(queue.begin()+i, entity);
				return;
			}
		}
			queue.push_back(entity);
	} else if( dynamic_cast<MOVE3*>(entity) ) {
		for(int i = 0; i < queue.size(); i++) {
			if( !dynamic_cast<MOVE1*>(queue[i]) ||
				!dynamic_cast<MOVE2*>(queue[i]) ) {
				queue.insert(queue.begin()+i, entity);
				return;
			}
		}
			queue.push_back(entity);
	} else if( dynamic_cast<MOVE4*>(entity) ) {
		for(int i = 0; i < queue.size(); i++) {
			if( !dynamic_cast<MOVE1*>(queue[i]) ||
				!dynamic_cast<MOVE2*>(queue[i]) ||
				!dynamic_cast<MOVE3*>(queue[i]) ) {
				queue.insert(queue.begin()+i, entity);
				return;
			}
		}
			queue.push_back(entity);
	} else if( dynamic_cast<MOVE5*>(entity) ) {
		for(int i = 0; i < queue.size(); i++) {
			if( !dynamic_cast<MOVE1*>(queue[i]) ||
				!dynamic_cast<MOVE2*>(queue[i]) ||
				!dynamic_cast<MOVE3*>(queue[i]) ||
				!dynamic_cast<MOVE4*>(queue[i]) ) {
				queue.insert(queue.begin()+i, entity);
				return;
			}
		}
			queue.push_back(entity);
	} else if( dynamic_cast<MOVE6*>(entity) ) {
		for(int i = 0; i < queue.size(); i++) {
			if( !dynamic_cast<MOVE1*>(queue[i]) ||
				!dynamic_cast<MOVE2*>(queue[i]) ||
				!dynamic_cast<MOVE3*>(queue[i]) ||
				!dynamic_cast<MOVE4*>(queue[i]) ||
				!dynamic_cast<MOVE5*>(queue[i]) ) {
				queue.insert(queue.begin()+i, entity);
				return;
			}
		}
			queue.push_back(entity);
	} else if( dynamic_cast<MOVE7*>(entity) ) {
		for(int i = 0; i < queue.size(); i++) {
			if( !dynamic_cast<MOVE1*>(queue[i]) ||
				!dynamic_cast<MOVE2*>(queue[i]) ||
				!dynamic_cast<MOVE3*>(queue[i]) ||
				!dynamic_cast<MOVE4*>(queue[i]) ||
				!dynamic_cast<MOVE5*>(queue[i]) ||
				!dynamic_cast<MOVE6*>(queue[i]) ) {
				queue.insert(queue.begin()+i, entity);
				return;
			}
		}
			queue.push_back(entity);
	}
}

void EnemyPlayer::update() {
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;

	if(queue.size() > 0) {

		if(current == 0) {
			current = queue.front();
			queue.erase(queue.begin() );
			if(current->enemyTurn()) {
				current = 0;
			}
		} else {
			Unit* unit = 0;
			unit = dynamic_cast<Unit*>(current);
			if(unit) {
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