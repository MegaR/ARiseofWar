#include "TileGrass.h"
#include "Game.h"

TileGrass::TileGrass(int x, int y) : Tile(x, y) {
	Game* game = &Game::getInstance();
	IAnimatedMesh* mesh = game->sceneManager->getMesh("res/tileGrass.3DS");
	node = game->sceneManager->addMeshSceneNode(mesh);
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture( 0, game->videoDriver->getTexture("res/tileGrassTexture.png") );
	node->setPosition(vector3d<f32>(x*10, 0, y*10) );
}


TileGrass::~TileGrass(void)
{
}
