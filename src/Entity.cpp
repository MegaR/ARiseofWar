#include "Entity.h"

#include <iostream>
using namespace std;

Entity::Entity(void)
{
}

Entity::~Entity()
{
	cout << "destroying Entity" << endl;
}


void Entity::startTurn()
{

}

void Entity::endTurn()
{

}

void Entity::render()
{

}

void Entity::update()
{
	
}

void Entity::selected() {

}

void Entity::deselected() {

}

bool Entity::inAttackRange(int x, int y, int attackDistance) {
	x = abs(tileX-x);
	y = abs(tileY-y);
	return ((x+y)<=attackDistance);
}