#pragma once

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class Game {
public:
	static Game& getInstance();

	void start();
	void loop();

	IrrlichtDevice* device;
	IVideoDriver* videoDriver;
	ISceneManager* sceneManager;
	IGUIEnvironment* gui;

	ICameraSceneNode* camera;


private:
	Game();
	Game(Game const&);
	void operator=(Game const&);
};