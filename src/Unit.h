#pragma once

#include "Entity.h"
#include <vector>
#include <time.h>
#include <stdlib.h>

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
	ISceneNode* node;

	void moveTo(int _tileX, int _tileY);
	void attackTarget(Entity* target);
	void addModel();
	void removeModel();
};