#pragma once
#include <vector>

#include "Scene.h"
#include "Game.h"
#include "Button.h"

class OptionsScene : public Scene
{
public:
	OptionsScene(void);
	~OptionsScene();

	void update();
	void start();

private:
	IGUIImage* background;
	IGUIStaticText* musicText;
	IGUIStaticText* soundEffectText;
	IGUIStaticText* shadowsText;

	Button* toggleMusicButton;
	Button* toggleSoundEffectsButton;
	Button* toggleShadowsButton;
	Button* saveSettingsButton;

	const wchar_t* wcMusic;
	const wchar_t* wcSoundEffects;
	const wchar_t* wcShadows;
};