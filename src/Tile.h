#pragma once

#include <irrlicht.h>
using namespace irr;
using namespace scene;

#include <time.h>
#include <stdlib.h>

class Tile
{
public:
	Tile(int x = 0, int y = 0);
	virtual ~Tile(void);

	bool walkable;
	IMeshSceneNode* node;

protected:
	void createModel(const irr::io::path model, const irr::io::path texture, int x, int y);
};
