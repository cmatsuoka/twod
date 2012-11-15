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

#include "image_map.h"

static int displayWidth, displayHeight;

twoDImageMap::twoDImageMap(){
	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_W, 0, 0);
	this->visible = true;
	this->collidable = false;
	this->autoFixCollision = false;
	this->oldX = this->x = 0;
	this->oldY = this->y = 0;

	this->image = NULL;
}

void twoDImageMap::update(twoDEngine *engine){
	int speed, mainLayer, dir;
	float multiplier;

	displayWidth = engine->getDisplayWidth();
	displayHeight = engine->getDisplayHeight();
	
	dir = TWOD_MOVE_DIRECTION_NONE;
	mainLayer = 0;

	if ((! this->scroll) && (! this->parallax))
		// image stands still
		speed = 0;
	else {
		// get speed, layer and direction of the main object

		if(engine->getMainObject() == NULL){
			speed = DEFAULT_SCROLL_SPEED;
			mainLayer = this->layer;
		}
		else if(engine->getMainObject()->hasMoved()){
			mainLayer = engine->getMainObject()->getLayer();
			speed = engine->getMainObject()->getMovement()->getSpeed();
			dir = engine->getMainObject()->getMovement()->getDirection();
		}
		else {
			speed = 0;
		}

		if(mainLayer == 0)
			mainLayer = 1;

		// calculates speed for the parallax effect
		if(this->parallax){
			// if scroll if set, the speed must be based on the main object 
			if(this->scroll)
				multiplier = (float)speed / mainLayer;
			else
				multiplier = this->parallaxMultiplier;
			speed = this->layer * multiplier;
		}
	}

	// scroll map based on the main object movement
	if(this->scroll && (dir != TWOD_MOVE_DIRECTION_NONE)){
		if((dir == TWOD_MOVE_DIRECTION_W) || (dir == TWOD_MOVE_DIRECTION_SW) || (dir == TWOD_MOVE_DIRECTION_NW))
			dir = TWOD_MOVE_DIRECTION_E;
		else if((dir == TWOD_MOVE_DIRECTION_E) || (dir == TWOD_MOVE_DIRECTION_SE) || (dir == TWOD_MOVE_DIRECTION_NE))
			dir = TWOD_MOVE_DIRECTION_W;
		else
			dir = TWOD_MOVE_DIRECTION_NONE;
		this->movement->setDirection(dir);

		// if this layer is where the main object is moving
		// then just the map must move if the main object is past the center
		if(this->layer == mainLayer){
			bool repositionate = false;
			
			if(this->repeat)
				repositionate = true;
			else {
				if((dir == TWOD_MOVE_DIRECTION_E) && (this->x < 0))
					repositionate = true;
				if((dir == TWOD_MOVE_DIRECTION_W) && ((this->x + this->width) > displayWidth))
					repositionate = true;
			}

			if(repositionate){
				int x, y, oldX, w;
				x = engine->getMainObject()->getX();
				oldX = engine->getMainObject()->getOldX();
				y = engine->getMainObject()->getY();
				w = engine->getMainObject()->getWidth();
				if(((dir == TWOD_MOVE_DIRECTION_W) && ((x + w/2) > (displayWidth/2))) 
					|| ((dir == TWOD_MOVE_DIRECTION_E) && ((x + w/2) < (displayWidth/2)))){
					engine->getMainObject()->setPosition(oldX, y);
				}
			}
		}
	}
	
	this->movement->setSpeed(speed);
	this->movement->update();
	this->movement->apply((twoDObject*)this);
}

void twoDImageMap::updatePosition(){
	if(this->image == NULL)
		return;

	if(this->scroll || this->parallax){
		if((! this->repeat) && ((this->x + this->width) <= displayWidth))
			this->x = displayWidth - this->width;
		if((! this->repeat) && ((this->x >= 0)))
			this->x = 0;

		if((this->x + this->width) <= 0)
			this->x = 0;
		else if(this->x >= displayWidth)
			this->x = this->x - this->width;
	}
}

void twoDImageMap::draw(){
	if(this->image == NULL)
		return;

	if(this->repeat){
		int w, x;
		w = this->image->getWidth();
		x = this->x;
		if(x <= 0)
			while(x < displayWidth){
				this->image->setPosition(x, this->y);
				this->image->draw();
				x += w;
			}
		else
			x = x - this->width;
			while(x < displayWidth){
				this->image->setPosition(x, this->y);
				this->image->draw();
				x += w;
			}
	}
	else {
		this->image->setPosition(this->x, this->y);
		this->image->draw();
	}
}

void twoDImageMap::collision(twoDObject *obj, int position){
}

void twoDImageMap::setImage(twoDImage *image){
	this->image = image;
	this->width = image->getWidth();
	this->height = image->getHeight();
}

