#pragma once

#include <iostream>
using namespace std;

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#include <irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "EventReceiver.h"

class Game {
public:
	static Game& getInstance();

	void start();
	void loop();
	void changeScene(Scene* newScene);

	IrrlichtDevice* device;
	IVideoDriver* videoDriver;
	ISceneManager* sceneManager;
	IGUIEnvironment* gui;

	Scene* currentScene;
	ICameraSceneNode* camera;
	EventReceiver* eventReceiver;

	int screenWidth;
	int screenHeight;
	f32 delta;

private:
	Game();
	Game(Game const&);
	void operator=(Game const&);

	void setGuiTheme();
};