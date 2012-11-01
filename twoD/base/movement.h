/*
 * twoD gaming engine
 * Copyright (C) 2012 Thiago Garrett
 *
 * twoD is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * twoD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with twoD. If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#ifndef _TWODMOVEMENT_H_
#define _TWODMOVEMENT_H_

// solve cross-reference
class twoDObject;

#include "../objects/object.h"

#define TWOD_MIN_SPEED 0
#define TWOD_MAX_SPEED 600
#define TWOD_MOVE_STEP 1

enum TWOD_DIRECTIONS {
	TWOD_MOVE_DIRECTION_N, // north
	TWOD_MOVE_DIRECTION_E, // east
	TWOD_MOVE_DIRECTION_W, // west
	TWOD_MOVE_DIRECTION_S, // south
	TWOD_MOVE_DIRECTION_NE, // northeast
	TWOD_MOVE_DIRECTION_NW, // northwest
	TWOD_MOVE_DIRECTION_SE, // southeast
	TWOD_MOVE_DIRECTION_SW // southwest
};

class twoDMovement {
private:
	int direction;
	int speed; // pixels per second
	int acceleration; 

public:
	twoDMovement(int, int, int);
	~twoDMovement();

	void update();
	void apply(twoDObject*);
	void speedUp(int s){ this->speed += s; }
	void speedDown(int s){ this->speed -= s; }
	void accelUp(int a){ this->acceleration += a; }
	void accelDown(int a){ this->acceleration -= a; }
	void turnRight();
	void turnLeft();
	void stop();

	// setters
	void setDirection(int d){ this->direction = d; }
	void setSpeed(int s){ this->speed = s; }
	void setAcceleration(int a){ this->acceleration = a; }

	// getters
	int getDirection(){ return this->direction; }
	int getSpeed(){ return this->speed; }
	int getAcceleration(){ return this->acceleration; }
};

#endif

