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
	this->stepCount = 0;
}

twoDMovement::~twoDMovement(){
}

void twoDMovement::update(){
	this->speed += this->acceleration;

	if(this->speed < TWOD_MIN_SPEED)
		this->speed = 0;
	else if(this->speed > TWOD_MAX_SPEED)
		this->speed = TWOD_MAX_SPEED;

	// TODO physics here ??
}

void twoDMovement::apply(twoDObject *obj){
	float stepSize;
	int moveX, moveY, steps;

	if((this->speed == 0) || (this->direction == TWOD_MOVE_DIRECTION_NONE))
		return;

	moveX = 0;
	moveY = 0;
	stepSize = (float)this->speed/TWOD_FPS;

	this->stepCount += stepSize;
	
	if(this->stepCount >= TWOD_MOVE_STEP){
		steps = this->stepCount / TWOD_MOVE_STEP;
		this->stepCount = 0;
	}
	else
		return;

	switch(this->direction){
		case TWOD_MOVE_DIRECTION_N:
			moveY -= steps;
			break;
		case TWOD_MOVE_DIRECTION_S:
			moveY += steps;
			break;
		case TWOD_MOVE_DIRECTION_E:
			moveX += steps;
			break;
		case TWOD_MOVE_DIRECTION_W:
			moveX -= steps;
			break;
		case TWOD_MOVE_DIRECTION_NE:
			moveX += steps;
			moveY -= steps;
			break;
		case TWOD_MOVE_DIRECTION_NW:
			moveX -= steps;
			moveY -= steps;
			break;
		case TWOD_MOVE_DIRECTION_SE:
			moveX += steps;
			moveY += steps;
			break;
		case TWOD_MOVE_DIRECTION_SW:
			moveX -= steps;
			moveY += steps;
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
		case TWOD_MOVE_DIRECTION_N:
			this->direction = TWOD_MOVE_DIRECTION_NE;
			break;
		case TWOD_MOVE_DIRECTION_S:
			this->direction = TWOD_MOVE_DIRECTION_SW;
			break;
		case TWOD_MOVE_DIRECTION_E:
			this->direction = TWOD_MOVE_DIRECTION_SE;
			break;
		case TWOD_MOVE_DIRECTION_W:
			this->direction = TWOD_MOVE_DIRECTION_NW;
			break;
		case TWOD_MOVE_DIRECTION_NE:
			this->direction = TWOD_MOVE_DIRECTION_E;
			break;
		case TWOD_MOVE_DIRECTION_NW:
			this->direction = TWOD_MOVE_DIRECTION_N;
			break;
		case TWOD_MOVE_DIRECTION_SE:
			this->direction = TWOD_MOVE_DIRECTION_S;
			break;
		case TWOD_MOVE_DIRECTION_SW:
			this->direction = TWOD_MOVE_DIRECTION_W;
			break;
	}
}

void twoDMovement::turnLeft(){
	switch(this->direction){
		case TWOD_MOVE_DIRECTION_N:
			this->direction = TWOD_MOVE_DIRECTION_NW;
			break;
		case TWOD_MOVE_DIRECTION_S:
			this->direction = TWOD_MOVE_DIRECTION_SE;
			break;
		case TWOD_MOVE_DIRECTION_E:
			this->direction = TWOD_MOVE_DIRECTION_NE;
			break;
		case TWOD_MOVE_DIRECTION_W:
			this->direction = TWOD_MOVE_DIRECTION_SW;
			break;
		case TWOD_MOVE_DIRECTION_NE:
			this->direction = TWOD_MOVE_DIRECTION_N;
			break;
		case TWOD_MOVE_DIRECTION_NW:
			this->direction = TWOD_MOVE_DIRECTION_W;
			break;
		case TWOD_MOVE_DIRECTION_SE:
			this->direction = TWOD_MOVE_DIRECTION_E;
			break;
		case TWOD_MOVE_DIRECTION_SW:
			this->direction = TWOD_MOVE_DIRECTION_S;
			break;
	}
}

void twoDMovement::turnOpposite(){
	this->turnRight();
	this->turnRight();
	this->turnRight();
	this->turnRight();
}

