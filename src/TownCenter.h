#pragma once
#include "building.h"
class TownCenter :
	public Building
{
public:
	TownCenter(int tileX, int tileY, int player);
	~TownCenter(void);
};

