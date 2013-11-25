#include "MenuScene.h"
#include "Game.h"
	
Button* playButton;
Button* exitButton;

MenuScene::MenuScene(void):Scene()
{
	Game* game = &Game::getInstance();
	
	int sW = game->screenWidth;
	int sH = game->screenHeight;
	int bW = 250, 
		bH = 100;
	int bX, bY;
	bX = (sW/2) - (bW/2);
	bY = (sH/2) - (bH/2);

	playButton = new Button(bX, bY-75, bW, bH, "Play");
	exitButton = new Button(bX, bY+75, bW, bH, "Exit");
}

MenuScene::~MenuScene()
{
	delete playButton;
	delete exitButton;
	cout << "MenuScene destructor" << endl;
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
		Game* game = &Game::getInstance();
		
		game->device->closeDevice();
		exit (1);
	}
}