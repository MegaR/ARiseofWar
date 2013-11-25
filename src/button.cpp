#include "Button.h"

Button::Button(int x, int y, int w, int h, std::string t)
{
	wstring ws;
	ws.assign(t.begin(), t.end());
	const wchar_t* btnText = ws.c_str();

	Game* game = &Game::getInstance();

	int x2 = x+w;
	int y2 = y+h;

	btn = game->gui->addButton(rect<s32>(x, y, x2, y2), 0, -1, btnText);
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