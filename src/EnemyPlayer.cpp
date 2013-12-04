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
	for(int i = 0; i < scene->entities.size(); i++) {
		if(scene->entities[i]->player == 1) {
			entityTurn(scene->entities[i]);
		}
	}
	scene->nextTurn();
}

void EnemyPlayer::entityTurn(Entity* current) {
	vector<Entity*>* targets = findTargets(current);
	
	for(int i = 0; i < targets->size(); i++) {
		if( attemptTarget(current, targets->at(i) ) ) {
			delete targets;
			return;
		}
	}

	cout << "turn failed!" << endl;
	delete targets;
}

bool EnemyPlayer::attemptTarget(Entity* current, Entity* target) {
	cout << "attemptTarget" << endl;
	Unit* currentUnit = ((Unit*)current);
	if(!currentUnit->hasAttacked && 
		target->inAttackRange(current->tileX, current->tileY, currentUnit->attackDistance) ) {
		currentUnit->attackTarget(target);
		cout << "attacked" << endl;
	}


	if(!currentUnit->hasMoved) {
		vector2d<int> destination = availableTile(current, target);
		if(destination != vector2d<int>(-1, -1) ) {
			currentUnit->moveTo(destination.X, destination.Y);
			cout << "moved?" << endl;
			if(!currentUnit->hasMoved) return false;
			cout << "moved!" << endl;
			attemptTarget(current, target);
			return true;
		} else {
			cout << "no route!?" << endl;
		}
	}

	if(currentUnit->hasMoved && currentUnit->hasAttacked) {
		return true;
	}

	return false;
}

vector2d<int> EnemyPlayer::availableTile(Entity* current, Entity* target) {
	GameScene* scene = (GameScene*) (Game::getInstance().currentScene);
	vector2d<int> tile(-1, -1);
	vector<vector2d<int>> candidates;

	if( target->tileX+1 < MAPSIZE && !scene->getEntity(target->tileX+1, target->tileY) ) {
		candidates.push_back(vector2d<int>(target->tileX+1, target->tileY) );
	}
	if( target->tileX-1 >= 0 &&  !scene->getEntity(target->tileX-1, target->tileY) ) {
		candidates.push_back(vector2d<int>(target->tileX-1, target->tileY) );
	}
	if( target->tileY+1 < MAPSIZE &&  !scene->getEntity(target->tileX, target->tileY+1) ) {
		candidates.push_back(vector2d<int>(target->tileX, target->tileY+1) );
	}
	if( target->tileY-1 >= 0 &&  !scene->getEntity(target->tileX, target->tileY-1) ) {
		candidates.push_back(vector2d<int>(target->tileX, target->tileY-1) );
	}
	
	float lowest = FLT_MAX;
	for(int i = 0; i < candidates.size(); i++) {
		float distance = candidates[i].getDistanceFrom(vector2d<int>(current->tileX, current->tileY) );
		if(distance < lowest ) {
			tile = candidates[i];
			lowest = distance;
		}
	}

	return tile;
}

vector<Entity*>* EnemyPlayer::findTargets(Entity* current) {
	GameScene* scene = (GameScene*) (Game::getInstance().currentScene);
	
	vector<Entity*>* targets = new vector<Entity*>();
	
	for(int i = 0; i < scene->entities.size(); i++) {
		if(scene->entities[i]->player == 1) continue;
		
		bool inserted = false;
		for(int ii = 0; ii < targets->size(); ii++) {
			if( targets->at(ii)->distance(current) > scene->entities[i]->distance(current) ) {
				targets->insert(targets->begin()+ii, scene->entities[i]);
				inserted = true;
				break;
			}
		}

		if(!inserted) {
			targets->push_back(scene->entities[i]);
		}
	}

	return targets;
}