#pragma once
#include "Building.h"

#define FARMCOST 10, 5, 5, 15
#define FARMINCREASE 0, -10, 0, 0

class Farm : public Building
{
public:
	Farm(int tileX, int tileY, int player, Scene* scene);
	~Farm(void);
	virtual void startTurn();
};

