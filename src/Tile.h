#pragma once

#include <irrlicht.h>
using namespace irr;
using namespace scene;

#include <time.h>
#include <stdlib.h>
#include "Entity.h"

class Tile
{
public:
	Tile(int x = 0, int y = 0);
	virtual ~Tile(void);

	bool walkable;
	IMeshSceneNode* node;
	Entity* getEntity();
	void setEntity(Entity* entity);

protected:
	void createModel(const irr::io::path model, const irr::io::path texture, int x, int y);
private:
	Entity* entity;
};
