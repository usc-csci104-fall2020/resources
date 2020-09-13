#include "player.h"

#include <iostream>
using namespace std;

Player::Player(string name) {
	hp_ = 500;
	maxhp_ = 500;
	name_ = name;
	inv = new Inventory();
}

Player::~Player() {
	delete inv;
}

Inventory* Player::getInv() {
	return inv;
}

int Player::getHP() {
	return hp_;
}

int Player::getMaxHP() {
	return maxhp_;
}

void Player::setHP(int hp) {
	hp_ = hp;
}

string Player::getName() {
	return name_;
}

bool Player::isDead() {
	return hp_ <= 0;
}

void Player::doAction(Player * target){
	cout << "Nothing to do..." << endl;
	
	if(!target) return;
}