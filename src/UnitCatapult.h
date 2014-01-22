#pragma once
#include "Unit.h" 

#define CATAPULTCOST 20, 0, 0, 10
#define CATAPULTBUILDTIME 5

class UnitCatapult : public Unit
{
public:

	void addModel();
	UnitCatapult(int _x, int _y, int _player, Scene* scene);
	~UnitCatapult(void);
};

