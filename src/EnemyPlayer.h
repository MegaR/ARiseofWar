#pragma once
#include "Player.h"
#include "GameScene.h"
#include "Unit.h"

#include <iostream>
using namespace std;

#define MOVE1 UnitPeasant
#define MOVE2 UnitKnight
#define MOVE3 UnitArcher
#define MOVE4 UnitSpearman
#define MOVE5 UnitCatapult
#define MOVE6 TownCenter
#define MOVE7 Barracks
#define MOVE8 SiegeWorkshop

class EnemyPlayer :
	public Player
{
public:
	EnemyPlayer(void);
	~EnemyPlayer(void);

	void turn();
	void update();
private:
	Entity* current;
	std::vector<Entity*> queue;
	void insertToQueue(Entity* entity);
};