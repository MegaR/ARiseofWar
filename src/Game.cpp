#include "Game.h"

Game::Game() {}
Game& Game::getInstance() {
	static Game instance;
	return instance;
}

void Game::start() {
	eventReceiver = new EventReceiver();

	#ifdef _DEBUG
	device = createDevice( video::EDT_OPENGL, dimension2d<u32>(800, 600), 16,
        false, false, false, eventReceiver);
	screenWidth = 800;
	screenHeight = 600;
	#else
	IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
	core::dimension2d<u32> deskres = nulldevice->getVideoModeList()->getDesktopResolution();
	nulldevice -> drop();
	device = createDevice(video::EDT_OPENGL, deskres, 32, true, false, true, 0);
	screenWidth = deskres.Width;
	screenHeight = deskres.Height;
	#endif

	if (!device) return;
	device->setWindowCaption(L"A Rise of War");
	
	videoDriver = device->getVideoDriver();
	sceneManager = device->getSceneManager();
	gui = device->getGUIEnvironment();

	camera = sceneManager->addCameraSceneNode(0, vector3df(0, 50, -40));
	camera->setID(0);
	sceneManager->setAmbientLight(SColorf(.25f, .25f, .25f));

	changeScene(new MenuScene());

	loop();
	device->drop();
	delete eventReceiver;
	return;
}

void Game::changeScene(Scene* newScene) {
	delete currentScene;
	currentScene = newScene;
	currentScene->start();
}

void Game::loop() {
	u32 prevTime = device->getTimer()->getTime();

	while(device->run()) {
		delta = (f32)(device->getTimer()->getTime() - prevTime) / 1000.f;
		prevTime = device->getTimer()->getTime();
		eventReceiver->update();

		videoDriver->beginScene(true, true, SColor(255,0,0,0));
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
