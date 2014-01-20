#pragma once
#include "Building.h"

#define LUMBERMILLCOST 10, 0, 0, 0
#define LUMBERMILLINCREASE -10, 0, 0, 0

class Lumbermill : public Building
{
public:
	Lumbermill(int tileX, int tileY, int player, Scene* scene);
	~Lumbermill(void);
	virtual void startTurn();
};

