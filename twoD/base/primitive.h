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

#ifndef _TWODPRIMITIVE_H_
#define _TWODPRIMITIVE_H_

#include<string>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
using namespace std;

#include "color.h"
#include "image.h"

#define TWOD_PRIMITIVE_MAX_VERTICES 100

// types
#define TWOD_PRIMITIVE_POINT_LIST ALLEGRO_PRIM_POINT_LIST
#define TWOD_PRIMITIVE_LINE_LOOP ALLEGRO_PRIM_LINE_LOOP
#define TWOD_PRIMITIVE_TRIANGLE_LIST ALLEGRO_PRIM_TRIANGLE_LIST
#define TWOD_PRIMITIVE_TRIANGLE_STRIP ALLEGRO_PRIM_TRIANGLE_STRIP
#define TWOD_PRIMITIVE_TRIANGLE_FAN ALLEGRO_PRIM_TRIANGLE_FAN

class twoDPrimitive {
private:
	twoDImage *texture;
	twoDColor *color;
	ALLEGRO_VERTEX vertices[TWOD_PRIMITIVE_MAX_VERTICES];
	int numVertices;
	int type;

public:
	twoDPrimitive();
	~twoDPrimitive();

	void draw();
	void addVertex(float, float);
	void addVertex(float, float, float, float);
	void move(float, float);

	// setters
	void setColor(twoDColor *c){ this->color = c; }
	void setType(int t){ this->type = t; }
	void setTexture(string);

	// getters
	twoDImage * getTexture(){ return this->texture; }
};

#endif

