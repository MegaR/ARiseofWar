#include "Player.h"
#include "Game.h"

Player::Player(void) {
	wood = 10;
	food = 20;
	gold = 5;
	stone = 20;

	top = NULL;
}


Player::~Player(void) {
	if(top) {
		top->remove();
		woodIcon->remove();
		foodIcon->remove();
		stoneIcon->remove();
		goldIcon->remove();
		woodText->remove();
		foodText->remove();
		stoneText->remove();
		goldText->remove();
	}
}

void Player::createGui() {
	Game* game = &Game::getInstance();
	IGUIEnvironment* gui = game->gui;

	top = gui->addImage(rect<s32>(0,0, game->screenWidth, 40));
	top->setImage(Game::getInstance().videoDriver->getTexture("res/guiBackgroundMenu.png"));

	woodIcon = gui->addImage(rect<s32>(4, 4, 36, 36));
	woodIcon->setImage(Game::getInstance().videoDriver->getTexture("res/guiWood.png"));
	woodText = gui->addStaticText(L"500", rect<s32>(40, 8, 100, 40) );

	foodIcon = gui->addImage(rect<s32>(100, 4, 132, 36));
	foodIcon->setImage(Game::getInstance().videoDriver->getTexture("res/guiFood.png"));
	foodText = gui->addStaticText(L"500", rect<s32>(136, 8, 196, 40) );

	stoneIcon = gui->addImage(rect<s32>(196, 4, 228, 36));
	stoneIcon->setImage(Game::getInstance().videoDriver->getTexture("res/guiStone.png"));
	stoneText = gui->addStaticText(L"500", rect<s32>(232, 8, 292, 40) );

	goldIcon = gui->addImage(rect<s32>(292, 4, 324, 36));
	goldIcon->setImage(Game::getInstance().videoDriver->getTexture("res/guiGold.png"));
	goldText = gui->addStaticText(L"500", rect<s32>(328, 8, 388, 40) );

	useResources(0,0,0,0);
}

bool Player::hasResources(int wood, int food, int gold, int stone) {
	if(this->wood >= wood && this->food >= food && this->gold >= gold && this->stone >= stone) {
		return true;
	}
	return false;
}

void Player::useResources(int wood, int food, int gold, int stone) {
	this->wood -= wood;
	this->food -= food;
	this->gold -= gold;
	this->stone -= stone;
	if(top) {
		std::wstring text = to_wstring(((long long)this->wood));
		woodText->setText( text.c_str() );
		text = to_wstring(((long long)this->food));
		foodText->setText( text.c_str() );
		text = to_wstring(((long long)this->gold));
		goldText->setText( text.c_str() );
		text = to_wstring(((long long)this->stone));
		stoneText->setText( text.c_str() );
	}
}

void Player::startTurn(){
	cout << "wood: " << wood << endl;
	cout << "food: " << food << endl;
	cout << "stone: " << stone << endl;
	cout << "gold: " << gold << endl;
}

void Player::endTurn(){

}

void Player::update() {
}