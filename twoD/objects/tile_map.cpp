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

#include "tile_map.h"

static int displayWidth, displayHeight;

twoDTileMap::twoDTileMap(){
	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_W, 0, 0);
	this->visible = true;
	this->collidable = false;
	this->autoFixCollision = false;
	this->oldX = this->x = 0;
	this->oldY = this->y = 0;
}

void twoDTileMap::update(twoDEngine *engine){
	int speed, mainLayer, dir;
	float multiplier;

	displayWidth = engine->getDisplayWidth();
	displayHeight = engine->getDisplayHeight();
	
	dir = TWOD_MOVE_DIRECTION_NONE;
	mainLayer = 0;

	if ((! this->scroll) && (! this->parallax))
		// stands still
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
		if((this->layer == mainLayer)){
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
	this->movement->apply((twoDObject*)this);
}

void twoDTileMap::updatePosition(){
	if(this->scroll || this->parallax){
		int moveX;

		if((! this->repeat) && (this->x < 0))
			this->x = 0;
		if((! this->repeat) && ((this->x + this->width) > displayWidth))
			this->x = displayWidth - this->width;
		
		moveX = this->x - this->oldX;

		// tile reset
		list<twoDMapTile*>::iterator i;
		for(i=this->tiles.begin(); i != this->tiles.end(); i++){
			int x, w;
			
			(*i)->x += moveX;
			x = (*i)->x;
			w = (*i)->image->getWidth();
			
			if((x + w) <= 0)
				x = x + displayWidth;
			
			if(x >= displayWidth)
				x = 0;

			(*i)->x = x;
		}
	}
}

void twoDTileMap::draw(){
	int x, y;

	if(this->repeat){
		// draw tiles
		list<twoDMapTile*>::iterator i;
		int w;
		for(i=this->tiles.begin(); i != this->tiles.end(); i++){
			x = (*i)->x;
			y = (*i)->y;
			w = (*i)->image->getWidth();

			(*i)->image->setPosition(x, y);
			(*i)->image->draw();

			// loop tiles to the left
			if(x <= 0){
				(*i)->image->setPosition(x + displayWidth, y);
				(*i)->image->draw();
//				(*i)->image->setPosition(x, y);
			}
			
			// loop tiles to the right
			if((x + w) >= displayWidth){
				(*i)->image->setPosition(x - displayWidth, y);
				(*i)->image->draw();
//				(*i)->image->setPosition(x, y);
			}
		}
	}
	else {
		// draw tiles
		list<twoDMapTile*>::iterator i;
		for(i=this->tiles.begin(); i != this->tiles.end(); i++){
			x = (*i)->x;
			y = (*i)->y;
			(*i)->image->setPosition(x, y);
			(*i)->image->draw();
		}
	}
}

void twoDTileMap::collision(twoDObject *obj, int position){
}

void twoDTileMap::addTile(twoDImage *img, int x, int y){
	twoDMapTile *tile = new twoDMapTile;
	tile->x = x;
	tile->y = y;
	tile->image = img;
	this->addTile(tile);
}

void twoDTileMap::addTile(twoDMapTile *tile){
	if(this->tiles.empty()){
		this->setInitialPosition(tile->x, tile->y);
		this->width = tile->image->getWidth();
		this->height = tile->image->getHeight();
	}

	this->tiles.push_back(tile);

	// update the map position and size to match the new tile inserted
	if(tile->x < this->x){
		this->width += (this->x - tile->x);
		this->x = tile->x;
	}
	
	if(tile->y < this->y){
		this->height += (this->y - tile->y);
		this->y = tile->y;
	}
	
	if((tile->x + tile->image->getWidth()) > (this->x + this->width)){
		this->width += ((tile->x + tile->image->getWidth()) - (this->x + this->width));
	}
	
	if((tile->y + tile->image->getHeight()) > (this->y + this->height)){
		this->height += ((tile->y + tile->image->getHeight()) - (this->y + this->height));
	}
}

