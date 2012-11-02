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

#ifndef _TWODSPRITE_H_
#define _TWODSPRITE_H_

#include<string>
#include<fstream>
#include "image.h"
#include "color.h"
#include "../engine.h"
using namespace std;

class twoDSprite {
private:
	twoDImage **image;
	int x, y;
	int width, height;
	int numImg;
	int switchRate;
	int imgCount;
	float switchCount;

public:
	twoDSprite(string); // sprite definition file
	~twoDSprite();

	void draw(); // draw sprite
	void move(int mx, int my){ this->x += mx; this->y += my; }

	// setters
	void setSize(int,int);
	void setPosition(int x, int y){ this->x = x; this->y = y; }
	void setSwitchRate(int s){ this->switchRate = s; }

	// getters
	int getX(){ return this->x; }
	int getY(){ return this->y; }
	int getWidth(){ return this->width; }
	int getHeight(){ return this->height; }
};

#endif

