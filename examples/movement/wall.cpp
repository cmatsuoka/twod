#include "wall.h"


standingWall::standingWall(string imgfile, int x, int y, int repeat){
	this->image = new twoDImage(imgfile);
	this->image->setPosition(x, y);

	this->visible = true;
	this->collidable = true;
	this->layer = 0;
	this->state = TWOD_STATE_STANDING;
	this->width = this->image->getWidth();
	this->height = this->image->getHeight() * repeat;
	this->repeat = repeat;
	this->x = x;
	this->y = y;
	this->oldX = x;
	this->oldY = y;

	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_NONE, 0, 0);
}

void standingWall::draw(){
	for(int i=0; i<this->repeat; i++){
		this->image->setPosition(this->x,this->y+(i*this->image->getHeight()-1));
		this->image->draw();
	}
}

void standingWall::update(twoDEngine *engine){
	this->moved = false;
}

void standingWall::collision(twoDObject *obj, int position){
}

void standingWall::updatePosition(){
}

