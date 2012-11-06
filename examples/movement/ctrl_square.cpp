#include "ctrl_square.h"

#include<iostream>
using namespace std;

controlledSquare::controlledSquare(int size, twoDColor *color){
	this->primitive = new twoDPrimitive();
	this->primitive->setColor(color);
	this->primitive->setType(TWOD_PRIMITIVE_TRIANGLE_FAN);
	this->primitive->addVertex(0,0);
	this->primitive->addVertex(size-1,0);
	this->primitive->addVertex(size-1,size-1);
	this->primitive->addVertex(0,size-1);

	this->x = 0;
	this->y = 0;
	this->visible = true;
	this->collidable = true;
	this->autoFixCollision = true;
	this->layer = 0;
	this->state = TWOD_STATE_STANDING;
	this->width = size;
	this->height = size;

	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_NONE, 0, 0);
}

void controlledSquare::update(twoDEngine *engine){
	bool up, down, left, right;
	int dir;

	up = down = left = right = false;
	dir = -1;

	if(engine->keyPressed(KEY_UP))
		up = true;
	if(engine->keyPressed(KEY_DOWN))
		down = true;
	if(engine->keyPressed(KEY_LEFT))
		left = true;
	if(engine->keyPressed(KEY_RIGHT))
		right = true;
	if(engine->keyPressed(KEY_SPACE))
		this->movement->stop();
	if(engine->keyPressed(KEY_A))
		this->movement->speedUp(SPEED_STEP);
	if(engine->keyPressed(KEY_S))
		this->movement->speedDown(SPEED_STEP);

	if(up)
		if(left)
			dir = TWOD_MOVE_DIRECTION_NW;
		else if(right)
			dir = TWOD_MOVE_DIRECTION_NE;
		else
			dir = TWOD_MOVE_DIRECTION_N;
	else if(down)
		if(left)
			dir = TWOD_MOVE_DIRECTION_SW;
		else if(right)
			dir = TWOD_MOVE_DIRECTION_SE;
		else
			dir = TWOD_MOVE_DIRECTION_S;
	else if(left)
		dir = TWOD_MOVE_DIRECTION_W;
	else if(right)
		dir = TWOD_MOVE_DIRECTION_E;

	this->movement->update();
	if(dir > -1){
		this->movement->setDirection(dir);
		this->movement->apply((twoDObject*)this);
	}
}

void controlledSquare::updatePosition(){
	int moveX, moveY;
	
	if(this->state == TWOD_STATE_COLLIDING){
		this->state = TWOD_STATE_MOVING;
	}

	// update position if moved
	if((this->x != this->oldX) || (this->y != this->oldY)){
		moveX = this->x - this->oldX;
		moveY = this->y - this->oldY;
		this->primitive->move(moveX, moveY);
	}
}

void controlledSquare::draw(){
	this->primitive->draw();
}

void controlledSquare::collision(twoDObject *obj, int position){
	cout << "Square collided !" << endl;
}

