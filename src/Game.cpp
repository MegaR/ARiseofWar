#include "Game.h"

Game::Game() {}
Game& Game::getInstance() {
	static Game instance;
	return instance;
}

void Game::start() {
	device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(800, 600), 16,
        false, false, false, 0);

	if (!device) return;
	device->setWindowCaption(L"A Rise of War");
	
	videoDriver = device->getVideoDriver();
	sceneManager = device->getSceneManager();
	gui = device->getGUIEnvironment();

	/*IAnimatedMesh* mesh = smgr->getMesh("../../media/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
	}*/
	camera = sceneManager->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

	changeScene(new MenuScene());

	loop();
	device->drop();
	return;
}

void Game::changeScene(Scene* newScene) {
	if(currentScene) {
		delete currentScene;
	}

	currentScene = newScene;
	currentScene->start();
}

void Game::loop() {
	while(device->run()) {
		videoDriver->beginScene(true, true, SColor(255,100,101,140));

		currentScene->update();

		sceneManager->drawAll();
		gui->drawAll();

		videoDriver->endScene();
	}
}

int main() {
	Game *game;
	game = &Game::getInstance();
	game->start();
	return 0;
}
