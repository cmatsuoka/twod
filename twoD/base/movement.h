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

#include "../objects/object.h"

enum TWOD_DIRECTIONS {
	TWOD_MODE_DIRECTION_N, // north
	TWOD_MODE_DIRECTION_E, // east
	TWOD_MODE_DIRECTION_W, // west
	TWOD_MODE_DIRECTION_S, // south
	TWOD_MODE_DIRECTION_NE, // northeast
	TWOD_MODE_DIRECTION_NW, // northwest
	TWOD_MODE_DIRECTION_SE, // southeast
	TWOD_MODE_DIRECTION_SW // southwest
};

class twoDMovement {
private:
	int direction;
	int speed;
	int acceleration;

public:
	twoDMovement(int, int, int);
	~twoDMovement();

	void update();
	void apply(twoDObject*);
	void speedUp(int s){ this->speed += s; }
	void speedDown(int s){ this->speed -= s; }
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

