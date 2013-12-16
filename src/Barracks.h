#pragma once
#include "building.h"
#include "UnitKnight.h"
class Barracks : public Building
{
public:
	Barracks(int tileX, int tileY, int player);
	~Barracks(void);
	void update();
	void createUnit();
};

