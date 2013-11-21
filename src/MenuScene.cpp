#include "MenuScene.h"


MenuScene::MenuScene(void)
{
	Game* game = &Game::getInstance();
	game->gui->addStaticText(L"W00T this is a test", rect<s32>(10,10,260,22), true);
	IGUIButton* button = game->gui->addButton(rect<s32>(50,50,120,100), 0, -1, L"QQQQQQQ");
}


MenuScene::~MenuScene(void)
{
}
