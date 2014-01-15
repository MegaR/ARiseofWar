#pragma once

#include <vector>
#include <irrlicht.h>
#include "Scene.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Entity
{
public:
	Entity(Scene* scene);
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

	virtual bool handleDamage(int damage);
	std::vector<vector2d<int>>* getSurroundingTiles();

	void render();
	virtual void update();

	vector2d<int> getVector();
	float distance(Entity* other);
	void cameraFocus();

	virtual bool inAttackRange(int x, int y, int attackDistance);
protected:
	Scene* scene;
};