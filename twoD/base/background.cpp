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

#include "background.h"

twoDBackground::twoDBackground(twoDImage *image){
	this->image = image;
	this->color = NULL;
}

twoDBackground::twoDBackground(twoDColor *color){
	this->color = color;
	this->image = NULL;
}

twoDBackground::twoDBackground(twoDColor *color, twoDImage *image){
	this->image = image;
	this->color = color;
}

twoDBackground::~twoDBackground(){
}

void twoDBackground::draw(){
	if(this->color != NULL)
		al_clear_to_color(this->color->map());
	if(this->image != NULL)
		this->image->draw();
}

twoDColor* twoDBackground::removeColor(){
	twoDColor *tmp;
	tmp = this->color;
	this->color = NULL;
	return tmp;
}

twoDImage* twoDBackground::removeImage(){
	twoDImage *tmp;
	tmp = this->image;
	this->image = NULL;
	return tmp;
}

