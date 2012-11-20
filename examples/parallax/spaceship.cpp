#include "spaceship.h"

spaceShip::spaceShip(){
	this->image = new twoDImage(SPACESHIP_IMAGE);
	this->image->setAlpha(new twoDColor(0x08, 0x21, 0x52));
	this->width = this->image->getWidth();
	this->height = this->image->getHeight();

	this->x = 0;
	this->y = 0;
	this->visible = true;
	this->collidable = true;
	this->autoFixCollision = true;
	this->layer = 0;
	this->state = TWOD_STATE_STANDING;

	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_NONE, 0, 0);
}

void spaceShip::update(twoDEngine *engine){
	bool up, down, left, right;
	int dir;
	
	this->moved = false;

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

	if(dir > -1){
		this->movement->setDirection(dir);
		this->movement->apply((twoDObject*)this);
	}
}

void spaceShip::updatePosition(){
	int moveX, moveY;
	
	if(this->state == TWOD_STATE_COLLIDING){
		this->state = TWOD_STATE_MOVING;
	}

	moveX = this->x - this->oldX;
	moveY = this->y - this->oldY;
	this->image->move(moveX, moveY);
}

void spaceShip::draw(){
	this->image->draw();
}

void spaceShip::collision(twoDObject *obj, int position){
}

