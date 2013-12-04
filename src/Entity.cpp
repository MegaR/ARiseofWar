#include "Entity.h"
#include "game.h"
#include <iostream>
using namespace std;

Entity::Entity(void)
{
}

Entity::~Entity()
{
	node->removeAll();
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

void Entity::handleDamage(int damage){
	hp -= damage;

	if( hp < 0){
		GameScene* scene = (GameScene*)Game::getInstance().currentScene;
		scene->removeEntity(this);
		return;
	}
}

vector2d<int> Entity::getVector() {
	return vector2d<int>(tileX, tileY);
}

float Entity::distance(Entity* other) {
	return getVector().getDistanceFrom(other->getVector());
}