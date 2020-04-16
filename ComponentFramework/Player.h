#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"

//Created by Noah.C

class Player : public Unit{

private:



public:

	//Create a new player by reading player defaults from the file.
	///TODO - Create file reader.
	Player();
	//Create a new player with a set maxHealth/curHealth.
	//Current health cannot exceed maxHealth.
	Player(Vec3 pos_, float maxHealth_, float curHealth_);
	~Player();

	//Takes in a direction vector to determine the direction the character will move.
	virtual void move(Vec3 dirVector_);

};
#endif
