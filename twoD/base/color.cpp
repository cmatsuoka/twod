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

#include "color.h"

twoDColor::twoDColor(int red, int green, int blue){
	this->red = red;
	this->green = green;
	this->blue = blue;
}

twoDColor::~twoDColor(){
}

twoDColor::twoDColor(string id){
	this->red = 0;
	this->green = 0;
	this->blue = 0;

	if(id == "red")
		this->red = 255;
	else if(id == "green")
		this->green = 255;
	else if(id == "blue")
		this->blue = 255;
	else if(id == "white"){
		this->red = 255;
		this->green = 255;
		this->blue = 255;
	}
}

ALLEGRO_COLOR twoDColor::map(){
	return al_map_rgb(this->red, this->green, this->blue);
}

