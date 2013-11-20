#pragma once
#include "Entity.h"
class Unit :
	public Entity
{
public:
	Unit(void);
	~Unit(void);

	int attack;
	int defence;
	int maxDistance;
	int attackDistance;
	// moveAnimation
	// attackanimation

	void move();
	//void attack(Entity tartget);
};

