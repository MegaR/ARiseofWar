#pragma once
#include "Building.h"

#define LUMBERMILLCOST 10, 0, 10, 10
#define LUMBERMILLINCREASE -10, 0, 0, 0

class LumberMill : public Building
{
public:
	LumberMill(int tileX, int tileY, int player, Scene* scene);
	~LumberMill(void);
	virtual void startTurn();
};

