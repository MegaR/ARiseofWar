#include "Button.h"
#include "Game.h"
Button::Button(int x, int y, int w, int h, std::string t, std::string tt, ITexture* _img)
{
	wstring ws;
	ws.assign(t.begin(), t.end());
	const wchar_t* btnText = ws.c_str();

	int x2 = x+w;
	int y2 = y+h;

	if (tt != "")
	{
		wstring wss;
		wss.assign(tt.begin(), tt.end());
		const wchar_t* btnTooltip = wss.c_str();

		btn = Game::getInstance().gui->addButton(rect<s32>(x, y, x2, y2), 0, -1, btnText, btnTooltip);
	}
	else
	{
		btn = Game::getInstance().gui->addButton(rect<s32>(x, y, x2, y2), 0, -1, btnText);
	}

	img = _img;
	if (img)
	{ 
		btn->setImage(img, rect<s32>(0,0,w,h)); 
		btn->setDrawBorder(0);
		btn->setUseAlphaChannel(true);
	}

	pressed = false;
	updated = false;
}

Button::~Button()
{
	btn->remove();
}

void Button::update()
{
	if (pressed)
	{
		updated = true;
	}

	if (btn->isPressed()) 
	{ 
		if (!updated)
		{
			pressed = true;
		} 
		else pressed = false;
	}
	else //btn released
	{ 
		pressed = false; 
		updated = false; 
	}
}