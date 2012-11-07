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

#include "border.h"

twoDBorder::twoDBorder(int border, int displayW, int displayH){
	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_NONE, 0, 0);
	this->visible = false;
	this->collidable = true;
	this->autoFixCollision = false;

	switch(border){
		case TWOD_BORDER_LEFT:
			this->x = 0;
			this->y = 0;
			this->width = 1;
			this->height = displayH;
			break;
		case TWOD_BORDER_RIGHT:
			this->x = displayW - 2;
			this->y = 0;
			this->width = 1;
			this->height = displayH;
			break;
		case TWOD_BORDER_TOP:
			this->x = 0;
			this->y = 0;
			this->width = displayW;
			this->height = 1;
			break;
		case TWOD_BORDER_BOTTOM:
			this->x = 0;
			this->y = displayH - 2;
			this->width = displayW;
			this->height = 1;
			break;
	}
	this->oldX = this->x;
	this->oldY = this->y;
}

void twoDBorder::update(twoDEngine *engine){
	this->moved = false;
}

void twoDBorder::updatePosition(){
}

void twoDBorder::draw(){
}

void twoDBorder::collision(twoDObject *obj, int position){
}

