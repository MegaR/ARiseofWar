#include "Tile.h"
#include "Game.h"

Tile::Tile(int x, int y)
{
	IMeshSceneNode* cube = Game::getInstance().sceneManager->addCubeSceneNode(10, 0, -1, vector3df(x*11,0,y*11) );
	cout << "x=" << x << " y=" << y << endl;
}


Tile::~Tile(void)
{
}
