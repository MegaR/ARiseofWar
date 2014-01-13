#include "Entity.h"
#include "game.h"
#include <iostream>
using namespace std;

Entity::Entity(Scene* scene)
{
	this->scene = scene;
}

Entity::~Entity()
{
	node->remove();
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

std::vector<vector2d<int>>* Entity::getSurroundingTiles() {
	vector<vector2d<int>>* tiles = new vector<vector2d<int>>();

	if(tileX-1 > 0) tiles->push_back(vector2d<int>(tileX-1, tileY));
	if(tileX+1 < MAPSIZE) tiles->push_back(vector2d<int>(tileX+1, tileY));
	if(tileY-1 > 0) tiles->push_back(vector2d<int>(tileX, tileY-1));
	if(tileY+1 < MAPSIZE) tiles->push_back(vector2d<int>(tileX, tileY+1));

	return tiles;
}

void Entity::deselected() {

}

bool Entity::inAttackRange(int x, int y, int attackDistance) {
	x = abs(tileX-x);
	y = abs(tileY-y);
	return ((x+y)<=attackDistance);
}

bool Entity::handleDamage(int damage){
	hp -= damage;
	cout << hp << endl;

	if( hp <= 0){
		GameScene* scene = (GameScene*)Game::getInstance().currentScene;
		scene->removeEntity(this);
		return false;
	}

	return true;
}

vector2d<int> Entity::getVector() {
	return vector2d<int>(tileX, tileY);
}

float Entity::distance(Entity* other) {
	return getVector().getDistanceFrom(other->getVector());
}

void Entity::enemyTurn() {
}

void Entity::cameraFocus() {
	Game* game = &Game::getInstance();
	ISceneNodeAnimator* animator = game->sceneManager->createFlyStraightAnimator(game->camera->getPosition(), vector3df(tileX*10, game->camera->getPosition().Y, tileY*10), 1000);
	game->camera->addAnimator(animator);
	game->camera->setTarget(vector3df(tileX*10, 0, tileY*10+5));
}