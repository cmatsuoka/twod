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

#ifndef _TWODOBJECT_H_
#define _TWODOBJECT_H_

// solve cross-reference
class twoDEngine;

#include "../engine.h"
//#include "../base/movement.h"

// objects states
#define TWOD_STATE_STANDING 1
#define TWOD_STATE_MOVING 2
#define TWOD_STATE_JUMPING 4
#define TWOD_STATE_COLLIDING 8

class twoDObject {
protected:
	int x, y;
	int width, height;
	int layer;
	int state;
	bool visible;
	bool collidable;
//	twoDMovement *movement;

public:
	virtual void draw() = 0;
	virtual void update(twoDEngine*) = 0;
	virtual void collision(twoDObject*) = 0;

	// getters
	int getX(){ return this->x; }
	int getY(){ return this->y; }
	int getWidth(){ return this->width; }
	int getHeight(){ return this->height; }
	int getLayer(){ return this-> layer; }
	int getState(){ return this->state; }
	bool isVisible(){ return this->visible; }
	bool isCollidable(){ return this->collidable; }

	// setters
	void setPosition(int x, int y){ this->x = x; this->y = y; }
	void setSize(int w, int h){ this->width = w; this->height = h; }
	void setLayer(int l){ this->layer = l; }
	void setState(int s){ this->state = s; }
	void setVisible(bool v){ this->visible = v; }
	void setCollidable(bool c){ this->collidable = c; }
};

#endif

