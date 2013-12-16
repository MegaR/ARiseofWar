#pragma once

#include "Entity.h"
#include <vector>
#include <time.h>
#include <stdlib.h>

#define WALKSPEED 300

#define IDLE_ANIMATION 0
#define WALKING_ANIMATION 1
#define ATTACKING_ANIMATION 2
#define DEATH_ANIMATION 3

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

	short currentAnimation;
	bool isAnimating[4];

	virtual void startTurn();
	virtual void enemyTurn();
	virtual void endTurn();
	// moveAnimation
	// attackAnimation

	std::vector<IAnimatedMeshSceneNode*> modelNodes;
	std::vector<vector2d<int>> path;

	void moveTo(int _tileX, int _tileY);
	void update();
	void updateAnimations();
	void attackTarget(Entity* target);
	void addModel();
	void removeModel();
	void followPath();
	void selected();
	void deselected();
	bool inAttackRange(int x, int y, int attackDistance);
	virtual void handleDamage(int damage);

private:
	void addDistanceTiles(int x, int y, int distance);
	std::vector<ISceneNode*> distanceTiles;

	std::vector<Entity*>* findTargets();
	bool attemptTarget(Entity* target);
	vector2d<int> availableTile(Entity* target);
	
	ISceneNodeAnimator* moveAnimator;
	float getAngleBetween(const vector3df& vec1, const vector3df& vec2);
};