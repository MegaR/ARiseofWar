#include "OptionsScene.h"
//#include "Game.h"

Game* game;

Button* toggleMusicButton;
Button* toggleSoundEffectsButton;
Button* toggleShadowsButton;
Button* saveSettingsButton;

IGUIStaticText* musicText;
IGUIStaticText* soundEffectText;
IGUIStaticText* shadowsText;

wstring wsMusicOn;
wstring wsSoundEffectOn;
wstring wsShadowsOn;

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

	background = game->gui->addImage(rect<s32>(0,0, game->screenWidth, game->screenHeight));
	background->setImage(game->videoDriver->getTexture("res/guiBackgroundMenu.png"));
	background->setScaleImage(true);

	if (game->musicOn == true) wsMusicOn = L"Music: ON";
	else wsMusicOn = L"Music: OFF";

	if (game->soundEffectsOn == true) wsSoundEffectOn = L"Sound Effects: ON";
	else wsSoundEffectOn = L"Sound Effects: OFF";

	if (game->shadowsOn == true) wsShadowsOn = L"Shadows: ON";
	else wsShadowsOn = L"Shadows: OFF";

	const wchar_t* wcMusicOn = wsMusicOn.c_str();
	const wchar_t* wcSoundEffectOn = wsSoundEffectOn.c_str();
	const wchar_t* wcShadowsOn = wsShadowsOn.c_str();

	musicText = game->gui->addStaticText(wcMusicOn, rect<s32>(45, bY-35, 550, bY-35+20));
	soundEffectText = game->gui->addStaticText(wcSoundEffectOn, rect<s32>(45, bY, 550, bY+20));
	shadowsText = game->gui->addStaticText(wcShadowsOn, rect<s32>(45, bY+35, 550, bY+35+20));

	ITexture* buttonTexture = Game::getInstance().videoDriver->getTexture("res/guiButtonToggle.png");
	toggleMusicButton = new Button(bX, bY-35, bW, bH, "", "Click to toggle the music!", buttonTexture);
	toggleSoundEffectsButton = new Button(bX, bY, bW, bH, "", "Click to toggle the sound effects!", buttonTexture);
	toggleShadowsButton = new Button(bX, bY+35, bW, bH, "", "Click to toggle the shadows!", buttonTexture);
	
	ITexture* buttonBackTexture = Game::getInstance().videoDriver->getTexture("res/guiButtonWide.png");
	saveSettingsButton = new Button(sW-250-10, sH-100-10, 250, 100, "Back to Menu", "Save settings and return to menu.", buttonBackTexture); 

	BGM = createIrrKlangDevice();
	if (Game::getInstance().musicOn == true) BGM->play2D("res/bgmMenu.mp3", true);
}

OptionsScene::~OptionsScene()
{
	delete toggleMusicButton;
	delete toggleSoundEffectsButton;
	delete toggleShadowsButton;
	delete saveSettingsButton;
	BGM->drop();
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

	if (toggleMusicButton->pressed == true)
	{
		game->musicOn = !game->musicOn;
		if (game->musicOn == true) wsMusicOn = L"Music: ON";
		else wsMusicOn = L"Music: OFF";
	}

	if (toggleSoundEffectsButton->pressed == true)
	{
		game->soundEffectsOn = !game->soundEffectsOn;
		if (game->soundEffectsOn == true) wsSoundEffectOn = L"Sound Effects: ON";
		else wsSoundEffectOn = L"Sound Effects: OFF";
	}

	if (toggleShadowsButton->pressed == true)
	{
		game->shadowsOn = !game->shadowsOn;
		if (game->shadowsOn == true) wsShadowsOn = L"Shadows: ON";
		else wsShadowsOn = L"Shadows: OFF";
	}

	if (saveSettingsButton->pressed == true)
	{
		Game::getInstance().changeScene(new MenuScene());
		musicText->remove();
		soundEffectText->remove();
		shadowsText->remove();
	}

	const wchar_t* wcMusicOn = wsMusicOn.c_str();
	const wchar_t* wcSoundEffectOn = wsSoundEffectOn.c_str();
	const wchar_t* wcShadowsOn = wsShadowsOn.c_str();

	musicText = game->gui->addStaticText(wcMusicOn, rect<s32>(45, bY-35, 550, bY-35+20));
	soundEffectText = game->gui->addStaticText(wcSoundEffectOn, rect<s32>(45, bY, 550, bY+20));
	shadowsText = game->gui->addStaticText(wcShadowsOn, rect<s32>(45, bY+35, 550, bY+35+20));
}