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
#include "OptionsScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "EventReceiver.h"

class Game {
public:
	static Game& getInstance();

	void start();
	void loop();
	void changeScene(Scene* newScene);
	ISound* playSound(const char* file, bool loop = false);

	IrrlichtDevice* device;
	IVideoDriver* videoDriver;
	ISceneManager* sceneManager;
	IGUIEnvironment* gui;
	ISoundEngine* soundEngine;

	Scene* currentScene;
	ICameraSceneNode* camera;
	EventReceiver* eventReceiver;

	int screenWidth;
	int screenHeight;
	f32 delta;

	bool musicOn;
	bool soundEffectsOn;
	bool shadowsOn;

private:
	Game();
	Game(Game const&);
	void operator=(Game const&);

	void setGuiTheme();
};