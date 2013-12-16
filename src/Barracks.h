#pragma once
#include "building.h"
class Barracks : public Building
{
public:
	Barracks(int tileX, int tileY, int player);
	~Barracks(void);
};

