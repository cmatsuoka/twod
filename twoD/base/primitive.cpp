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

#include "primitive.h"

static bool ALLEGRO_PRIMITIVE_ADDON_INIT = false;

twoDPrimitive::~twoDPrimitive(){
	if(this->texture != NULL)
		delete this->texture;
}

twoDPrimitive::twoDPrimitive(){
	if(!ALLEGRO_PRIMITIVE_ADDON_INIT){
		al_init_primitives_addon();
		ALLEGRO_PRIMITIVE_ADDON_INIT = true;
	}

	this->numVertices = 0;
	this->type = TWOD_PRIMITIVE_LINE_LOOP;
	this->texture = NULL;
	this->color = new twoDColor("white");
}

void twoDPrimitive::addVertex(float x, float y, float u, float v){
	struct ALLEGRO_VERTEX vertex;
	vertex.x = x;
	vertex.y = y;
	vertex.z = 0;
	vertex.u = u;
	vertex.v = v;
	vertex.color = this->color->map();
	this->vertices[this->numVertices++] = vertex;
}

void twoDPrimitive::addVertex(float x, float y){
	this->addVertex(x, y, 0.0, 0.0);
}

void twoDPrimitive::draw(){
	ALLEGRO_BITMAP* texture = NULL;

	if(this->texture != NULL)
		texture = this->texture->getBitmap();

	al_draw_prim(this->vertices, NULL, texture, 0, this->numVertices, this->type);
}

void twoDPrimitive::setTexture(string texturefile){
	this->texture = new twoDImage(texturefile);
}

void twoDPrimitive::move(float x, float y){
	for(int i=0; i<this->numVertices; i++){
		this->vertices[i].x += x;
		this->vertices[i].y += y;
	}
}


