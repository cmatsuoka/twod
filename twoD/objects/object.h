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
class twoDMovement;

#include "../engine.h"
#include "../base/movement.h"

// objects states
#define TWOD_STATE_STANDING 1
#define TWOD_STATE_MOVING 2
#define TWOD_STATE_JUMPING 4
#define TWOD_STATE_COLLIDING 8

class twoDObject {
protected:
	int x = 0, y = 0;
	int oldX = -1, oldY = -1;
	int width = 0, height = 0;
	int layer = 0;
	int state = TWOD_STATE_STANDING;
	bool visible = true;
	bool collidable = true;
	bool autoFixCollision = false;
	bool autoRedirectCollision = false;
	twoDMovement *movement = 0;

	virtual void updatePosition() = 0;

public:
	virtual void draw() = 0;
	virtual void update(twoDEngine*) = 0;
	virtual void collision(twoDObject*,int) = 0;

	void move(int mx, int my){ 
		this->oldX = this->x;
		this->oldY = this->y;
		this->x += mx; 
		this->y += my; 
		this->updatePosition(); 
	}

	// getters
	int getX(){ return this->x; }
	int getY(){ return this->y; }
	int getOldX(){ return this->oldX; }
	int getOldY(){ return this->oldY; }
	int getWidth(){ return this->width; }
	int getHeight(){ return this->height; }
	int getLayer(){ return this-> layer; }
	int getState(){ return this->state; }
	bool getAutoFixCollision(){ return this->autoFixCollision; }
	bool getAutoRedirectCollision(){ return this->autoRedirectCollision; }
	twoDMovement * getMovement(){ return this->movement; }
	bool isVisible(){ return this->visible; }
	bool isCollidable(){ return this->collidable; }

	// setters
	void setSize(int w, int h){ this->width = w; this->height = h; }
	void setLayer(int l){ this->layer = l; }
	void setState(int s){ this->state = s; }
	void setVisible(bool v){ this->visible = v; }
	void setCollidable(bool c){ this->collidable = c; }
	void setAutoFixCollision(bool a){ this->autoFixCollision = a; }
	void setAutoRedirectCollision(bool a){ this->autoRedirectCollision = a; }
	void setOldPosition(int x, int y){ this->oldX = this->x; this->oldY = this->y; }
	void setInitialPosition(int x, int y){ 
		this->setPosition(x,y); 
		this->setOldPosition(this->x, this->y);
	}		
	void setPosition(int x, int y){ 
		this->oldX = this->x;
		this->oldY = this->y;
		this->x = x; 
		this->y = y; 
		this->updatePosition(); 
	}
};

#endif

