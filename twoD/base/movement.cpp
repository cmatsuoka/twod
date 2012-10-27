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

#include "movement.h"

twoDMovement::twoDMovement(int direction, int speed, int acceleration){
	this->direction = direction;
	this->speed = speed;
	this->acceleration = acceleration;
}

twoDMovement::~twoDMovement(){
}

void twoDMovement::update(){
	this->speed += this->acceleration;

	// TODO physics here ??
}

void twoDMovement::apply(twoDObject *obj){
	int moveX, moveY;

	moveX = 0;
	moveY = 0;

	switch(this->direction){
		case TWOD_MODE_DIRECTION_N:
			moveY -= this->speed;
			break;
		case TWOD_MODE_DIRECTION_S:
			moveY += this->speed;
			break;
		case TWOD_MODE_DIRECTION_E:
			moveX += this->speed;
			break;
		case TWOD_MODE_DIRECTION_W:
			moveX -= this->speed;
			break;
		case TWOD_MODE_DIRECTION_NE:
			moveX += this->speed;
			moveY -= this->speed;
			break;
		case TWOD_MODE_DIRECTION_NW:
			moveX -= this->speed;
			moveY -= this->speed;
			break;
		case TWOD_MODE_DIRECTION_SE:
			moveX += this->speed;
			moveY += this->speed;
			break;
		case TWOD_MODE_DIRECTION_SW:
			moveX -= this->speed;
			moveY += this->speed;
			break;
	}

	obj->move(moveX, moveY);
}

void twoDMovement::stop(){
	this->speed = 0;
	this->acceleration = 0;
}

void twoDMovement::turnRight(){
	switch(this->direction){
		case TWOD_MODE_DIRECTION_N:
			this->direction = TWOD_MODE_DIRECTION_NE;
			break;
		case TWOD_MODE_DIRECTION_S:
			this->direction = TWOD_MODE_DIRECTION_SW;
			break;
		case TWOD_MODE_DIRECTION_E:
			this->direction = TWOD_MODE_DIRECTION_SE;
			break;
		case TWOD_MODE_DIRECTION_W:
			this->direction = TWOD_MODE_DIRECTION_NW;
			break;
		case TWOD_MODE_DIRECTION_NE:
			this->direction = TWOD_MODE_DIRECTION_E;
			break;
		case TWOD_MODE_DIRECTION_NW:
			this->direction = TWOD_MODE_DIRECTION_N;
			break;
		case TWOD_MODE_DIRECTION_SE:
			this->direction = TWOD_MODE_DIRECTION_S;
			break;
		case TWOD_MODE_DIRECTION_SW:
			this->direction = TWOD_MODE_DIRECTION_W;
			break;
	}
}

void twoDMovement::turnLeft(){
	switch(this->direction){
		case TWOD_MODE_DIRECTION_N:
			this->direction = TWOD_MODE_DIRECTION_NW;
			break;
		case TWOD_MODE_DIRECTION_S:
			this->direction = TWOD_MODE_DIRECTION_SE;
			break;
		case TWOD_MODE_DIRECTION_E:
			this->direction = TWOD_MODE_DIRECTION_NE;
			break;
		case TWOD_MODE_DIRECTION_W:
			this->direction = TWOD_MODE_DIRECTION_SW;
			break;
		case TWOD_MODE_DIRECTION_NE:
			this->direction = TWOD_MODE_DIRECTION_N;
			break;
		case TWOD_MODE_DIRECTION_NW:
			this->direction = TWOD_MODE_DIRECTION_W;
			break;
		case TWOD_MODE_DIRECTION_SE:
			this->direction = TWOD_MODE_DIRECTION_E;
			break;
		case TWOD_MODE_DIRECTION_SW:
			this->direction = TWOD_MODE_DIRECTION_S;
			break;
	}
}

