#pragma once
#include "Entity.h"

class Building : public Entity
{
public:
	Building(int tileX, int tileY, int player);
	~Building(void);
	void createModel();

	int sizeX;
	int sizeY;
};