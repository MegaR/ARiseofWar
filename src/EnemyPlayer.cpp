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
}

void EnemyPlayer::entityTurn(Entity* entity) {
	Entity* target = findNearestTarget(entity->tileX, entity->tileY);
	if(!target) {
		cout << "no target" << endl;
		return;
	}

	vector2d<int> destination = nearestTile(target->tileX, target->tileY, entity->tileX, entity->tileY);
	if(destination == vector2d<int>(-1,-1)) {
		cout << "no route to target" << endl;
		return;
	}

	((Unit*)entity)->moveTo(destination.X, destination.Y);
}

Entity* EnemyPlayer::findNearestTarget(int tileX, int tileY) {
	GameScene* scene = (GameScene*) (Game::getInstance().currentScene);
	Entity* nearestEntity = NULL;
	float nearestDistance = FLT_MAX;
	
	for(int i = 0; i < scene->entities.size(); i++) {
		if(scene->entities[i]->player == 1) continue;
		if(nearestEntity == NULL) nearestEntity = scene->entities[i];
	}

	return nearestEntity;
}

vector2d<int> EnemyPlayer::nearestTile(int tileX, int tileY, int originX, int originY) {
	vector2d<int> destination(-1,-1);
	float nearest;

	if(possibleDestination(tileX, tileY+1)) {
		destination = vector2d<int>(tileX, tileY+1);
	} else if(possibleDestination(tileX, tileY-1)) {
		destination = vector2d<int>(tileX, tileY-1);
	} else if(possibleDestination(tileX+1, tileY)) {
		destination = vector2d<int>(tileX+1, tileY);
	} else if(possibleDestination(tileX-1, tileY)) {
		destination = vector2d<int>(tileX-1, tileY);
	} 

	return destination;
}

bool EnemyPlayer::possibleDestination(int tileX, int tileY) {
	GameScene* scene = (GameScene*) (Game::getInstance().currentScene);
	
	if(tileX < 0 || tileX > MAPSIZE-1) {
		return false;
	}

	if(tileY < 0 || tileY > MAPSIZE-1) {
		return false;
	}
	
	if(scene->getEntity(tileX, tileY) ) {
		return false;
	}

	return true;
}