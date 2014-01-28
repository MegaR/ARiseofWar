#include "OptionsScene.h"
#include "Game.h"

Game* game;

Button* toggleMusicButton;
Button* toggleSoundEffectsButton;
Button* toggleShadowsButton;
Button* saveSettingsButton;

OptionsScene::OptionsScene(void):Scene()
{
	game = &Game::getInstance();
	
	int sW = game->screenWidth;
	int sH = game->screenHeight;
	int bW = 25, 
		bH = 25;
	int bX, bY;
	bX = 10;
	bY = (sH/2) - (bH/2);
	
	if (game->musicOn == true){ wcMusic = L"Music: ON"; }
	else { wcMusic = L"Music: OFF"; }
	if (game->soundEffectsOn == true){ wcSoundEffects = L"Sound Effects: ON"; }
	else { wcSoundEffects = L"Sound Effects: OFF"; }
	if (game->shadowsOn == true){ wcShadows = L"Shadows: ON"; }
	else { wcShadows = L"Shadows: OFF"; }

	musicText = game->gui->addStaticText(wcMusic, rect<s32>(45, bY-35, 550, bY-35+20));
	soundEffectText = game->gui->addStaticText(wcSoundEffects, rect<s32>(45, bY, 550, bY+20));
	shadowsText = game->gui->addStaticText(wcShadows, rect<s32>(45, bY+35, 550, bY+35+20));

	background = game->gui->addImage(rect<s32>(0,0, game->screenWidth, game->screenHeight));
	background->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
	background->setScaleImage(true);

	ITexture* buttonTexture = Game::getInstance().videoDriver->getTexture("res/guiButtonToggle.png");
	toggleMusicButton = new Button(bX, bY-35, bW, bH, "", "Click to toggle the music!", buttonTexture);
	toggleSoundEffectsButton = new Button(bX, bY, bW, bH, "", "Click to toggle the sound effects!", buttonTexture);
	toggleShadowsButton = new Button(bX, bY+35, bW, bH, "", "Click to toggle the shadows!", buttonTexture);
	
	ITexture* buttonBackTexture = Game::getInstance().videoDriver->getTexture("res/guiButtonWide.png");
	saveSettingsButton = new Button(sW-250-10, sH-100-10, 250, 100, "Back to Menu", "Save settings and return to menu.", buttonBackTexture); 
}

void OptionsScene::start() {
	if (Game::getInstance().musicOn == true) music = game->playSound("res/bgmMenu.mp3", true);
}

OptionsScene::~OptionsScene()
{
	if (musicText) { musicText->remove(); }
	if (soundEffectText) { soundEffectText->remove(); }
	if (shadowsText) { shadowsText->remove(); }

	delete toggleMusicButton;
	delete toggleSoundEffectsButton;
	delete toggleShadowsButton;
	delete saveSettingsButton;

	background->remove();
}

void OptionsScene::update()
{
	toggleMusicButton->update();
	toggleSoundEffectsButton->update();
	toggleShadowsButton->update();
	saveSettingsButton->update();

	int sH = game->screenHeight;
	int bY = (sH/2) - (25/2);

	if (musicText) { musicText->remove(); }
	if (soundEffectText) { soundEffectText->remove(); }
	if (shadowsText) { shadowsText->remove(); }

	if (game->musicOn == true){ wcMusic = L"Music: ON"; }
	else { wcMusic = L"Music: OFF"; }
	if (game->soundEffectsOn == true){ wcSoundEffects = L"Sound Effects: ON"; }
	else { wcSoundEffects = L"Sound Effects: OFF"; }
	if (game->shadowsOn == true){ wcShadows = L"Shadows: ON"; }
	else { wcShadows = L"Shadows: OFF"; }

	musicText = game->gui->addStaticText(wcMusic, rect<s32>(45, bY-35, 550, bY-35+20));
	soundEffectText = game->gui->addStaticText(wcSoundEffects, rect<s32>(45, bY, 550, bY+20));
	shadowsText = game->gui->addStaticText(wcShadows, rect<s32>(45, bY+35, 550, bY+35+20));

	musicText->setVisible(true);
	soundEffectText->setVisible(true);
	shadowsText->setVisible(true);

	if (toggleMusicButton->pressed == true)
	{
		game->musicOn = !game->musicOn;
		if (game->soundEffectsOn == true) Game::getInstance().playSound("res/seButtonClick.wav", false);
	}
	
	if (toggleSoundEffectsButton->pressed == true)
	{
		game->soundEffectsOn = !game->soundEffectsOn;
		if (game->soundEffectsOn == true) Game::getInstance().playSound("res/seButtonClick.wav", false);
	}

	if (toggleShadowsButton->pressed == true)
	{
		game->shadowsOn = !game->shadowsOn;
		if (game->soundEffectsOn == true) Game::getInstance().playSound("res/seButtonClick.wav", false);
	}

	if (saveSettingsButton->pressed == true)
	{
		if (game->soundEffectsOn == true) Game::getInstance().playSound("res/seButtonClick.wav", false);

		Game::getInstance().changeScene(new MenuScene());
	}
}