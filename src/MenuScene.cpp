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

	background = game->gui->addImage(rect<s32>(0,0, game->screenWidth, game->screenHeight));
	background->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
	background->setScaleImage(true);

	ITexture* buttonTexture = Game::getInstance().videoDriver->getTexture("res/guiButtonWide.png");
	playButton = new Button(bX, bY-75, bW, bH, "Play", "Click to play!", buttonTexture);
	exitButton = new Button(bX, bY+75, bW, bH, "Exit", "", buttonTexture);
}

MenuScene::~MenuScene()
{
	delete playButton;
	delete exitButton;
	background->remove();
}

void MenuScene::update()
{
	playButton->update();
	exitButton->update();
	
	if (playButton->pressed == true)
	{
		Game::getInstance().changeScene(new GameScene());
	}

	if (exitButton->pressed == true)
	{
		Game* game = &Game::getInstance();
		
		game->device->closeDevice();
		exit (1);
	}
}