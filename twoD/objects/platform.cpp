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

#include "platform.h"

twoDPlatform::twoDPlatform(twoDImage *tile){
	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_NONE, 0, 0);
	this->platform = true;
	this->visible = true;
	this->collidable = true;
	this->autoFixCollision = false;
	this->tile = tile;
	this->width = this->tile->getWidth();
	this->height = this->tile->getHeight();
	this->x = 0;
	this->y = 0;
	this->oldX = 0;
	this->oldY = 0;
}

twoDPlatform::twoDPlatform(int w, int h){
	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_NONE, 0, 0);
	this->platform = true;
	this->visible = false;
	this->collidable = true;
	this->autoFixCollision = false;
	this->tile = NULL;
	this->width = w;
	this->height = h;
	this->x = 0;
	this->y = 0;
	this->oldX = 0;
	this->oldY = 0;
}

void twoDPlatform::update(twoDEngine *engine){
	this->moved = false;
}

void twoDPlatform::updatePosition(){
}

void twoDPlatform::draw(){
	if(this->tile != NULL){
		this->tile->setPosition(this->x, this->y);
		this->tile->draw();
	}
}

void twoDPlatform::collision(twoDObject *obj, int position){
}

