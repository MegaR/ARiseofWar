#include "MenuScene.h"
//#include "Game.h"
	
Button* playButton;
Button* optionsButton;
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
	startGame = false;

	background = game->gui->addImage(rect<s32>(0,0, game->screenWidth, game->screenHeight));
	background->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
	background->setScaleImage(true);

	ITexture* buttonTexture = Game::getInstance().videoDriver->getTexture("res/guiButtonWide.png");
	playButton = new Button(bX, bY-125, bW, bH, "Play", "Click to play!", buttonTexture);
	optionsButton = new Button(bX, bY, bW, bH, "Settings", "", buttonTexture);
	exitButton = new Button(bX, bY+125, bW, bH, "Exit", "", buttonTexture);

	BGM = createIrrKlangDevice();
	if (Game::getInstance().musicOn == true) BGM->play2D("res/bgmMenu.mp3", true);

	loading = game->gui->addImage(rect<s32>((game->screenWidth / 2) - (960/2), (game->screenHeight / 2) - (540/2), game->screenWidth, game->screenHeight));
	loading->setImage(game->videoDriver->getTexture("res/guiLoading.png") );
	loading->setVisible(false);
}

MenuScene::~MenuScene()
{
	delete playButton;
	delete optionsButton;
	delete exitButton;
	BGM->drop();
	background->remove();
	loading->remove();
}

void MenuScene::update()
{
	playButton->update();
	optionsButton->update();
	exitButton->update();
	
	if (playButton->pressed == true)
	{
		Game* game = &Game::getInstance();
		loading->setVisible(true);
		startGame = true;
		return;
	}

	if(startGame) {
		if (Game::getInstance().soundEffectsOn == true) BGM->play2D("res/seButtonClick.wav", false);
		Game::getInstance().changeScene(new GameScene());
	}

	if (optionsButton->pressed == true)
	{
		if (Game::getInstance().soundEffectsOn == true) BGM->play2D("res/seButtonClick.wav", false);
		Game::getInstance().changeScene(new OptionsScene());
	}

	if (exitButton->pressed == true)
	{
		Game* game = &Game::getInstance();
		
		game->device->closeDevice();
		exit (1);
	}
}