#pragma once
#include "Unit.h" 

#define CATAPULTCOST 0, 0, 0, 0
#define CATAPULTBUILDTIME 2

class UnitCatapult : public Unit
{
public:

	void addModel();
	UnitCatapult(int _x, int _y, int _player, Scene* scene);
	~UnitCatapult(void);
};

