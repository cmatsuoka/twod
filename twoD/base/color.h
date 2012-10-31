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

#ifndef _TWODCOLOR_H_
#define _TWODCOLOR_H_

#include<allegro5/allegro.h>
#include<string>
using namespace std;

class twoDColor {
private:
	// RGB
	int red;
	int green;
	int blue;

public:
	twoDColor(int red, int green, int blue);
	twoDColor(string id); // preset colors
	~twoDColor();

	ALLEGRO_COLOR map();

	// getters
	int getRed(){ return this->red; }
	int getGreen(){ return this->green; }
	int getBlue(){ return this->blue; }
};

#endif

