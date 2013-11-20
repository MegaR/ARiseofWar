#pragma once

#ifdef _DEBUG
#include <Windows.h>
#endif

#include <stdio.h>
#include <iostream>
using namespace std;

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"

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

private:
	Game();
	Game(Game const&);
	void operator=(Game const&);
};