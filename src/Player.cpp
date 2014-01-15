#include "Player.h"
#include "Game.h"

Player::Player(void) {
	wood = 10;
	food = 0;
	stone = 10;
	gold = 0;

	Game* game = &Game::getInstance();
	IGUIEnvironment* gui = game->gui;
	IGUIImage* top = gui->addImage(rect<s32>(0,0, game->screenWidth, 40));
	top->setImage(Game::getInstance().videoDriver->getTexture("res/guiBackgroundMenu.png"));

	IGUIImage* woodIcon = gui->addImage(rect<s32>(4, 4, 36, 36));
	woodIcon->setImage(Game::getInstance().videoDriver->getTexture("res/guiWood.png"));

	IGUIImage* foodIcon = gui->addImage(rect<s32>(36, 4, 68, 36));
	foodIcon->setImage(Game::getInstance().videoDriver->getTexture("res/guiFood.png"));

	IGUIImage* stoneIcon = gui->addImage(rect<s32>(68, 4, 100, 36));
	stoneIcon->setImage(Game::getInstance().videoDriver->getTexture("res/guiStone.png"));

	IGUIImage* goldIcon = gui->addImage(rect<s32>(100, 4, 132, 36));
	goldIcon->setImage(Game::getInstance().videoDriver->getTexture("res/guiGold.png"));
}


Player::~Player(void) {

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
}

void Player::startTurn(){
	cout << "wood: " << wood << endl;
	cout << "food: " << food << endl;
	cout << "stone: " << stone << endl;
	cout << "gold: " << gold << endl;
}

void Player::endTurn(){

}