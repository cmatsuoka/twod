#include "square.h"

twoDSquare::twoDSquare(int size, twoDColor *color){
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
	this->layer = 0;
	this->state = TWOD_STATE_STANDING;
	this->width = size;
	this->height = size;

	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_E, 0, 0);
}

void twoDSquare::update(twoDEngine *engine){
	this->movement->update();
	this->movement->apply((twoDObject*)this);

	if(engine->keyPressed(KEY_UP))
		this->movement->speedUp(SPEED_STEP);
	if(engine->keyPressed(KEY_DOWN))
		this->movement->speedDown(SPEED_STEP);
	if(engine->keyPressed(KEY_LEFT))
		this->movement->turnLeft();
	if(engine->keyPressed(KEY_RIGHT))
		this->movement->turnRight();
	if(engine->keyPressed(KEY_SPACE))
		this->movement->stop();
}

void twoDSquare::updatePosition(int oldX, int oldY){
	int moveX, moveY;

	// update position if moved
	if((this->x != oldX) || (this->y != oldY)){
		moveX = this->x - oldX;
		moveY = this->y - oldY;
		this->primitive->move(moveX, moveY);
	}
}

void twoDSquare::draw(){
	this->primitive->draw();
}

void twoDSquare::collision(twoDObject *obj){
	this->movement->turnRight();
	this->movement->turnRight();
	this->movement->turnRight();
	this->movement->turnRight();
}

