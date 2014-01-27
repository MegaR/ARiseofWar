#pragma once
#include "Unit.h" 

#define CATAPULTCOST 20, 0, 10, 0
#define CATAPULTBUILDTIME 4 //actually 3?

class UnitCatapult : public Unit
{
public:

	void updateAnimations();
	void addModel();
	UnitCatapult(int _x, int _y, int _player, Scene* scene);
	~UnitCatapult(void);
};

