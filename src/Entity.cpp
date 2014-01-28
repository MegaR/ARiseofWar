#include "Entity.h"
#include "game.h"
#include <iostream>
using namespace std;

Entity::Entity(Scene* scene)
{
	this->scene = scene;
	Game* game = &Game::getInstance();
	this->hpText = game->gui->addStaticText(L"health: 100, attack: 10, defense: 50", rect<s32>(game->screenWidth - 350, 10,  game->screenWidth, 100));
	this->hpText->setVisible(false);
	attack = 0;
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
	hpText->setVisible(true);
	std::wstring text = L"hp: " + to_wstring((long long)hp ) + L", attack: " + to_wstring((long long) attack) + L", defense: " + to_wstring((long long) defense);
	hpText->setText( text.c_str() );
	((GameScene*)scene)->players[0]->topRight->setVisible(true);
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
	hpText->setVisible(false);
	((GameScene*)scene)->players[0]->topRight->setVisible(false);
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

bool Entity::enemyTurn() {
	return false;
}

void Entity::cameraFocus() {
	Game* game = &Game::getInstance();
	GameScene* scene = (GameScene*) this->scene;
	scene->cameraTarget = vector3df( (tileX+1)*10, game->camera->getPosition().Y, (tileY-1)*10);
}