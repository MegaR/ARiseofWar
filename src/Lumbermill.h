#pragma once
#include "Building.h"



class Lumbermill : public Building
{
public:
	Lumbermill(int tileX, int tileY, int player, Scene* scene) : Building(tileX, tileY, player, scene);
	~Lumbermill(void);
};

