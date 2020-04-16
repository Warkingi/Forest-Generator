#ifndef UNIT_H
#define UNIT_H

#include "VMath.h"

//Created by Noah.C

using namespace MATH;

class Unit {

protected:

	//TreeModel* model; Model Here...

	float curHealth, maxHealth, moveSpeed;

	Vec3 pos;

	virtual void move(Vec3 dirVector_) = 0;


public:

	inline float getCurrentHealth() const { return curHealth; } //Get the units current health.
	inline float getMaxHealth() const { return maxHealth; } //Get the units max health.
	inline float getMovementSpeed() const { return moveSpeed; } //Get the units current movement speed.
	inline Vec3 getPosition() const { return pos; } //Get the the position of the unit.


	inline float setMovementSpeed(float newSpeed_) { moveSpeed = newSpeed_; } //Set the new movement speed for the unit.

};
#endif
