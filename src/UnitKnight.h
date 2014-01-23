#pragma once

#include "Unit.h"

#define KNIGHTCOST 0, 10, 0, 10
#define KNIGHTBUILDTIME 3

class UnitKnight: public Unit
{
public:
	UnitKnight(int _x, int _y, int _player, Scene* scene);
	~UnitKnight();
	
	void selected();
	void update();
	void startTurn();
};

