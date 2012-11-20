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

#include<iostream>
using namespace std;

twoDMovement::twoDMovement(bool gravity){
	this->init(TWOD_MOVE_DIRECTION_NONE, 0, 0, gravity);
}

twoDMovement::twoDMovement(){
	this->init(TWOD_MOVE_DIRECTION_NONE, 0, 0, false);
}

twoDMovement::twoDMovement(int direction){
	this->init(direction, 0, 0, false);
}

twoDMovement::twoDMovement(int direction, int speed){
	this->init(direction, speed, 0, false);
}

twoDMovement::twoDMovement(int direction, int speed, int accel){
	this->init(direction, speed, accel, false);
}

twoDMovement::twoDMovement(int direction, int speed, int accel, bool gravity){
	this->init(direction, speed, accel, gravity);
}
void twoDMovement::init(int direction, int speed, int accel, bool gravity){
	this->direction = direction;
	this->speed = speed;
	this->accel = accel;
	this->gravity = gravity;

	this->jumping = false;
	this->jSpeed = 0;
	this->jAccel = TWOD_DEFAULT_JUMP_SPEED;
	this->gAccel = TWOD_DEFAULT_GRAVITY;
	this->gSpeed = 0;
	this->stepCount = 0;
	this->gStepCount = 0;
	this->fallingCount = 0;
}

twoDMovement::~twoDMovement(){
}

void twoDMovement::jump(){
	this->jumping = true;
	this->jSpeed = jAccel;
}

void twoDMovement::stopFalling(){
	this->fallingCount = 0; 
	this->jSpeed = 0;
	this->jumping = false;
}

void twoDMovement::update(){
	// increase speed
	this->speed += this->accel;
	if(this->speed < TWOD_MIN_SPEED)
		this->speed = TWOD_MIN_SPEED;
	else if(this->speed > TWOD_MAX_SPEED)
		this->speed = TWOD_MAX_SPEED;

	// gravity
	if(this->gravity){
		this->fallingCount++;
		this->gSpeed = this->fallingCount * gAccel;
	}
	else
		this->gSpeed = 0;
}

void twoDMovement::apply(twoDObject *obj){
	float stepSize, gStepSize, jStepSize;
	int moveX, moveY, steps = 0, gSteps = 0, jSteps = 0;

	this->update();

	moveX = 0;
	moveY = 0;
	stepSize = (float)this->speed/TWOD_FPS;
	gStepSize = (float)this->gSpeed/TWOD_FPS;
	jStepSize = (float)this->jSpeed/TWOD_FPS;

	this->stepCount += stepSize;
	this->gStepCount += gStepSize;
	this->jStepCount += jStepSize;
	
	if(this->stepCount >= TWOD_MOVE_STEP){
		steps = this->stepCount / TWOD_MOVE_STEP;
		this->stepCount = 0;
	}
	
	if(this->gStepCount >= TWOD_MOVE_STEP){
		gSteps = this->gStepCount / TWOD_MOVE_STEP;
		this->gStepCount = 0;
	}

	if(this->jStepCount >= TWOD_MOVE_STEP){
		jSteps = this->jStepCount / TWOD_MOVE_STEP;
		this->jStepCount = 0;
	}

	if((steps == 0) && (gSteps == 0) && (jSteps == 0)){
		obj->setState(TWOD_STATE_STANDING);
		return;
	}

	if(this->jumping)
		obj->setState(TWOD_STATE_JUMPING);
	else
		obj->setState(TWOD_STATE_MOVING);

	switch(this->direction){
		case TWOD_MOVE_DIRECTION_N:
			moveY = moveY - steps + gSteps - jSteps;
			if(moveY > 0){
				this->direction = TWOD_MOVE_DIRECTION_S;
			}
			break;
		case TWOD_MOVE_DIRECTION_S:
			moveY = moveY + steps + gSteps - jSteps;
			break;
		case TWOD_MOVE_DIRECTION_E:
			moveX += steps;
			if(gSteps > 0)
				moveY += gSteps;
			if(jSteps > 0)
				moveY -= jSteps;
			if(moveY > 0)
				this->direction = TWOD_MOVE_DIRECTION_SE;
			else if (moveY < 0)
				this->direction = TWOD_MOVE_DIRECTION_NE;
			break;
		case TWOD_MOVE_DIRECTION_W:
			moveX -= steps;
			if(gSteps > 0)
				moveY += gSteps;
			if(jSteps > 0)
				moveY -= jSteps;
			if(moveY > 0)
				this->direction = TWOD_MOVE_DIRECTION_SW;
			else if (moveY < 0)
				this->direction = TWOD_MOVE_DIRECTION_NW;
			break;
		case TWOD_MOVE_DIRECTION_NE:
			moveX += steps;
			moveY = moveY - steps + gSteps - jSteps;
			if(moveY > 0){
				this->direction = TWOD_MOVE_DIRECTION_SE;
			}
			break;
		case TWOD_MOVE_DIRECTION_NW:
			moveX -= steps;
			moveY = moveY - steps + gSteps - jSteps;
			if(moveY > 0){
				this->direction = TWOD_MOVE_DIRECTION_SW;
			}
			break;
		case TWOD_MOVE_DIRECTION_SE:
			moveX += steps;
			moveY = moveY + steps + gSteps - jSteps;
			if(moveY < 0){
				this->direction = TWOD_MOVE_DIRECTION_NE;
			}
			break;
		case TWOD_MOVE_DIRECTION_SW:
			moveX -= steps;
			moveY = moveY + steps + gSteps - jSteps;
			if(moveY < 0){
				this->direction = TWOD_MOVE_DIRECTION_NW;
			}
			break;
		case TWOD_MOVE_DIRECTION_NONE:
			if(gSteps > 0)
				moveY += gSteps;
			if(jSteps > 0)
				moveY -= jSteps;
			if(moveY < 0)
				this->direction = TWOD_MOVE_DIRECTION_N;
			else if(moveY > 0)
				this->direction = TWOD_MOVE_DIRECTION_S;
			break;
	}

	obj->move(moveX, moveY);
}

void twoDMovement::stop(){
	this->speed = 0;
	this->accel = 0;
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

