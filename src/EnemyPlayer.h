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
};