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


void Unit::moveTo(int _tileX, int _tileY)
{
	/*int distanceX = _tileX - tileX, 
		distanceY = _tileY - tileY;*/

	if (tileX < _tileX)
	{
		//moveAnimation
		tileX++;
	}
	else if (tileX > _tileX)
	{
		//moveAnimation
		tileX--;
	}
	else //tileX == _tileX (unit is at target)
	{
		//idleAnimation
		tileX = _tileX;
	}
	
	if (tileY < _tileY)
	{
		//moveAnimation
		tileY++;
	}
	else if (tileY > _tileY)
	{
		//moveAnimation
		tileY--;
	}
	else //tileY == _tileY (unit is at target)
	{
		//idleAnimation
		tileY = _tileY;
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