#pragma once

#include "Entity.h"

class Unit: public Entity
{
public:
	Unit(void);
	virtual ~Unit();

	int attack;
	int maxDistance;
	int attackDistance;
	// moveAnimation
	// attackAnimation

	void moveTo(int _tileX, int _tileY);
	void attackTarget(Entity* target);
};