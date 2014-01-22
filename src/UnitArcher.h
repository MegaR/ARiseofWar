#pragma once

#include "Unit.h"

#define ARCHERCOST 0, 10, 0, 10
#define ARCHERBUILDTIME 1

class UnitArcher: public Unit
{
public:
	UnitArcher(int _x, int _y, int _player, Scene* scene);
	~UnitArcher();
};

