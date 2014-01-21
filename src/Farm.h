#pragma once
#include "Building.h"

#define FARMCOST 10, 0, 0, 0
#define FARMINCREASE -10, 0, 0, 0

class Farm : public Building
{
public:
	Farm(int tileX, int tileY, int player, Scene* scene);
	~Farm(void);
	virtual void startTurn();
};

