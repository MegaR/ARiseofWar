#pragma once
#include "building.h"
#include "UnitKnight.h"
class Barracks : public Building
{
public:
	Barracks(int tileX, int tileY);
	~Barracks(void);
	void createUnit();
};

