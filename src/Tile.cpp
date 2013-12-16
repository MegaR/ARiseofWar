#include "Tile.h"
#include "Game.h"

Tile::Tile(int x, int y)
{
}


Tile::~Tile(void)
{
	node->remove();
}

void Tile::createModel(const path model, const path texture, int x, int y) {
	Game* game = &Game::getInstance();
	IAnimatedMesh* mesh = game->sceneManager->getMesh(model);
	node = game->sceneManager->addMeshSceneNode(mesh);
	//node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture( 0, game->videoDriver->getTexture(texture) );
	node->getMaterial(0).Shininess = 0;
	node->getMaterial(0).setFlag(EMF_ANISOTROPIC_FILTER, true);
	node->setPosition(vector3df(x*10, 0, y*10) );
	node->setRotation(vector3df(0,rand()%3*90,0));
	node->setID(1);

}