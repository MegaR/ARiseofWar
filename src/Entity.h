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

	void startTurn();
	void endTurn();

	virtual void selected();
	virtual void deselected();

	void render();
	virtual void update();

	bool inAttackRange(int x, int y, int attackDistance);

//protected:
	float x, y, z;
};