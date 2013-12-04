#pragma once

#include "Entity.h"
#include <vector>
#include <time.h>
#include <stdlib.h>

#define WALKSPEED 50

class Unit: public Entity
{
public:
	Unit(int tileX, int tileY, int player);
	virtual ~Unit();

	int attack;
	int maxDistance;
	int attackDistance;

	bool hasAttacked;
	bool hasMoved;

	virtual void startTurn();
	virtual void endTurn();
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
	void selected();
	void deselected();
	bool inAttackRange(int x, int y, int attackDistance);

private:
	void addDistanceTiles(int x, int y, int distance);

	std::vector<ISceneNode*> distanceTiles;
};