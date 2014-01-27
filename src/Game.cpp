#include "Game.h"

Game::Game() {}
Game& Game::getInstance() {
	static Game instance;
	return instance;
}

void Game::start() {
	srand(time(NULL));
	eventReceiver = new EventReceiver();

	#ifdef _DEBUG
	device = createDevice( video::EDT_OPENGL, dimension2d<u32>(800, 600), 16,
        false, false, false, eventReceiver);
	screenWidth = 800;
	screenHeight = 600;
	musicOn = false;
	soundEffectsOn = true;
	shadowsOn = true;
	#else
	IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
	core::dimension2d<u32> deskres = nulldevice->getVideoModeList()->getDesktopResolution();
	nulldevice -> drop();
	device = createDevice(video::EDT_OPENGL, deskres, 32, true, true, true, eventReceiver);
	screenWidth = deskres.Width;
	screenHeight = deskres.Height;
	musicOn = true;
	soundEffectsOn = true;
	shadowsOn = true;
	#endif

	if (!device) return;
	device->setWindowCaption(L"A Rise of War");
	
	videoDriver = device->getVideoDriver();
	sceneManager = device->getSceneManager();
	gui = device->getGUIEnvironment();

	setGuiTheme();

	camera = sceneManager->addCameraSceneNode(0);
	camera->setID(0);
	sceneManager->setAmbientLight(SColorf(.05f, .05f, .05f));
	sceneManager->setShadowColor(SColor(150,0,0,0));

	ILightSceneNode* light = sceneManager->addLightSceneNode(0, vector3df(-50,75, -50), SColorf(.75f,.75f,.75f), 195.f);
	camera->addChild(light);

	changeScene(new MenuScene());

	loop();
	device->drop();
	delete eventReceiver;
	return;
}

void Game::setGuiTheme() {
	IGUISkin* skin = gui->getSkin();
	IGUIFont* font = gui->getFont("res/Font.bmp");
	skin->setColor(EGDC_BUTTON_TEXT, SColor(255,255,255,255) );
	
	font->setKerningWidth(2);
	font->setKerningHeight(2);
	skin->setFont(font);
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
		

		videoDriver->beginScene(true, true, SColor(255,0,0,0));
		currentScene->update();
		sceneManager->drawAll();
		gui->drawAll();
		eventReceiver->update();
		videoDriver->endScene();
	}
}

int main() {
	Game *game;
	game = &Game::getInstance();
	game->start();
	return 0;
}
