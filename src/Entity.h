#pragma once

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Entity
{
public:
	Entity(void);
	virtual ~Entity();

	int tileX;
	int tileY;
	int player;
	int hp;
	int defense;

	IAnimatedMesh* model;
	ITexture* texture;
	ISceneNode* node;

	virtual void startTurn();
	virtual void enemyTurn();
	virtual void endTurn();

	virtual void selected();
	virtual void deselected();

	virtual void handleDamage(int damage);

	void render();
	virtual void update();

	vector2d<int> getVector();
	float distance(Entity* other);

	bool inAttackRange(int x, int y, int attackDistance);

//protected:
	float x, y, z;
};