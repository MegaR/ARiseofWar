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

private:
	IGUIImage* background;
	IGUIStaticText* musicText;
	IGUIStaticText* soundEffectText;
	IGUIStaticText* shadowsText;

	const wchar_t* wcMusic;
	const wchar_t* wcSoundEffects;
	const wchar_t* wcShadows;

	ISoundEngine* BGM;
};