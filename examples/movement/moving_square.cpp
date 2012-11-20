#include "moving_square.h"

movingSquare::movingSquare(int size, twoDColor *color){
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
	this->autoRedirectCollision = true;
	this->layer = 0;
	this->state = TWOD_STATE_STANDING;
	this->width = size;
	this->height = size;

	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_SW, 200, 0);
}

void movingSquare::update(twoDEngine *engine){
	this->moved = false;
	this->movement->apply((twoDObject*)this);
}

void movingSquare::updatePosition(){
	int moveX, moveY;
	
	if(this->state == TWOD_STATE_COLLIDING){
		this->state = TWOD_STATE_MOVING;
	}

	moveX = this->x - this->oldX;
	moveY = this->y - this->oldY;
	this->primitive->move(moveX, moveY);
}

void movingSquare::draw(){
	this->primitive->draw();
}

void movingSquare::collision(twoDObject *obj, int position){
}

