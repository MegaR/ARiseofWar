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
	vector<Entity*>* findTargets(Entity* current);
	bool attemptTarget(Entity* current, Entity* target);
	vector2d<int> availableTile(Entity* current, Entity* target);
};

