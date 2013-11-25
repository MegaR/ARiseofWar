#include "MenuScene.h"
#include "Game.h"
	
Button* playButton;
Button* exitButton;

MenuScene::MenuScene(void):Scene()
{
	Game* game = &Game::getInstance();
	
	int w = game->screenWidth;
	int h = game->screenHeight;

	
	playButton = new Button(275, 150, 250, 100, "Play");
	exitButton = new Button(275, 300, 250, 100, "Exit");
}

MenuScene::~MenuScene()
{
	delete playButton;
	delete exitButton;
	cout << "MenuScene destructor" << endl;
}

//playButton::onClick(){ do this }
//exitButton::onClick(){ ... }

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