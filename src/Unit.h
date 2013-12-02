#pragma once

#include "Entity.h"
#include <vector>
#include <time.h>
#include <stdlib.h>

#define WALKSPEED 1

class Unit: public Entity
{
public:
	Unit(int tileX, int tileY, int player);
	virtual ~Unit();

	int attack;
	int maxDistance;
	int attackDistance;
	// moveAnimation
	// attackAnimation

	std::vector<IAnimatedMeshSceneNode*> modelNodes;
	std::vector<vector2d<int>> path;
	ISceneNode* node;

	void moveTo(int _tileX, int _tileY);
	void update();
	void attackTarget(Entity* target);
	void addModel();
	void removeModel();
	void followPath();
};