#include "TileSystem.h"
#include "Game.h"

TileSystem::TileSystem(void)
{
	cout << "Filling tilemap" << endl;
	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			tiles[x][y] = new TileGrass(x,y);
		}
	}

	Game* game = &Game::getInstance();
	IAnimatedMesh* mesh = game->sceneManager->getMesh("res/selected.3DS");
	IMeshSceneNode* node = game->sceneManager->addMeshSceneNode(mesh);
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	node->setMaterialTexture( 0, game->videoDriver->getTexture("res/selectedTexture.png") );
	node->setPosition(vector3d<f32>(50, 0, 50) );
	node->setID(0);
}

TileSystem::~TileSystem(void)
{
	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			delete tiles[x][y];
		}
	}
}