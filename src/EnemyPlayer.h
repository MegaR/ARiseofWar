#pragma once
#include "Player.h"
#include "GameScene.h"
#include "Unit.h"

#include <iostream>
using namespace std;

#define MOVE1 UnitPeasant
#define MOVE2 UnitKnight
#define MOVE3 UnitArcher
#define MOVE4 UnitCatapult
#define MOVE5 TownCenter
#define MOVE6 Barracks
#define MOVE7 SiegeWorkshop

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