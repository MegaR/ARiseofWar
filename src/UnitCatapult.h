#pragma once
#include "Unit.h" 

#define CATAPULTCOST 0, 10, 10, 0
#define CATAPULTBUILDTIME 8

class UnitCatapult : public Unit
{
public:
	UnitCatapult(int _x, int _y, int _player, Scene* scene);
	~UnitCatapult(void);
};

