#include "Button.h"

Button::Button(int x, int y, int w, int h, std::string t, ITexture* _img)
{
	wstring ws;
	ws.assign(t.begin(), t.end());
	const wchar_t* btnText = ws.c_str();

	int x2 = x+w;
	int y2 = y+h;

	btn = Game::getInstance().gui->addButton(rect<s32>(x, y, x2, y2), 0, -1, btnText);
	img = _img;
	if (img)
	{ 
		btn->setImage(img, rect<s32>(0,0,w,h)); 
		btn->setUseAlphaChannel(true);
	}

	pressed = false;
}

Button::~Button()
{
	btn->remove();
}

void Button::update()
{
	if (btn->isPressed()) { pressed = true; }
	else { pressed = false; }
}