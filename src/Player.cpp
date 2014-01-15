#include "Player.h"


Player::Player(void) {
	wood = 10;
	food = 0;
	stone = 10;
	gold = 0;
}


Player::~Player(void)
{
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