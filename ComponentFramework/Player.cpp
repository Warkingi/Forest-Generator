#include "Player.h"

//Created by Noah.C

Player::Player() {
	///TODO
	maxHealth = 100.0f;
	curHealth = 100.0f;

	moveSpeed = 0.5f;
}

Player::Player(Vec3 pos_, float maxHealth_, float curHealth_) {

	maxHealth = maxHealth_;
	if (curHealth_ > maxHealth_) { //If a player is created with a current health higher than maxHealth, just set curHealth equal to maxHealth.
		curHealth = maxHealth_;
	}
	else {
		curHealth = curHealth_;
	}

}

Player::~Player() {

}

void Player::move(Vec3 dirVector_) {



}