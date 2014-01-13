#pragma once
#include "Entity.h"

class Building : public Entity
{
public:
	Building(int tileX, int tileY, int player, Scene* scene);
	~Building(void);
	void createModel();
	std::vector<vector2d<int>>* getSurroundingTiles();
	virtual bool inAttackRange(int x, int y, int attackDistance);

	int sizeX;
	int sizeY;
};