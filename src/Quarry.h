#pragma once
#include "Building.h"

#define QUARRYCOST 0, 0, 0, 10
#define QUARRYINCREASE 0, 0, 0, -10

class Quarry : public Building
{
public:
	Quarry(int tileX, int tileY, int player, Scene* scene);
	~Quarry(void);
	virtual void startTurn();
};
