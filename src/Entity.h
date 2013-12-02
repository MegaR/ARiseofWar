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
	bool selected;

	void startTurn();
	void endTurn();

	void render();
	void update();

//protected:
	float x, y, z;
};