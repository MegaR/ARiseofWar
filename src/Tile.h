#pragma once

#include <irrlicht.h>
using namespace irr;
using namespace scene;

class Tile
{
public:
	Tile(int x = 0, int y = 0);
	~Tile(void);

	//Model model;
	IMeshSceneNode* node;

};
