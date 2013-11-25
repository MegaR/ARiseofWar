#include "MenuScene.h"
#include "Game.h"
	
	Button* playButton;
	Button* exitButton;

MenuScene::MenuScene(void):Scene()
{
	playButton = new Button(50, 50, 250, 100, "Play");
	exitButton = new Button(50, 200, 250, 100, "Exit");
}

MenuScene::~MenuScene(void)
{
	delete playButton;
	delete exitButton;
}

void MenuScene::update()
{
	playButton->update();
	exitButton->update();
	
	if (playButton->pressed == true)
	{
		//button* poop = new button(1, 1, 50, 50, "POOP");
		Game::getInstance().changeScene(new GameScene());
	}

	if (exitButton->pressed == true)
	{
		//Game.device->closeDevice();
	}
}