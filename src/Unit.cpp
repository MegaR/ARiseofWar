#include "Unit.h"

#include <iostream>
using namespace std;

Unit::Unit(void)
{
}

Unit::~Unit()
{
	cout << "destroying Unit" << endl;
}


void Unit::moveTo(int desX, int desY)
{
	/*int distanceX = desX - tileX, 
		distanceY = desY - tileY;*/

	if (tileX < desX)
	{
		//moveAnimation
		tileX++;
	}
	else if (tileX > desX)
	{
		//moveAnimation
		tileX--;
	}
	else //tileX == desX (unit is at target)
	{
		//idleAnimation
		tileX = desX;
	}
	
	if (tileY < desY)
	{
		//moveAnimation
		tileY++;
	}
	else if (tileY > desY)
	{
		//moveAnimation
		tileY--;
	}
	else //tileY == desY (unit is at target)
	{
		//idleAnimation
		tileY = desY;
	}
}

void Unit::attackTarget(Entity* target)
{
	if (target->defense >= attack)
	{
		//attackAnimation
		target->hp--;
	}
	else
	{
		//attackAnimation
		target->hp -= (attack - target->defense);
	}
}