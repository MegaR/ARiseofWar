#pragma once
#include "Player.h"
#include "GameScene.h"
#include "Unit.h"

#include <iostream>
using namespace std;

class EnemyPlayer :
	public Player
{
public:
	EnemyPlayer(void);
	~EnemyPlayer(void);

	void turn();
private:
	void entityTurn(Entity* entity);
	Entity* findNearestTarget(int tileX, int tileY);
	vector2d<int> nearestTile(int tileX, int tileY, int originX, int originY);
	bool possibleDestination( int tileX, int tileY);
};

