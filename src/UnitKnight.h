#pragma once

#include "Unit.h"

#define KNIGHTCOST 0, 10, 10, 0
#define KNIGHTBUILDTIME 3

class UnitKnight: public Unit
{
public:
	UnitKnight(int _x, int _y, int _player, Scene* scene);
	~UnitKnight();
};

