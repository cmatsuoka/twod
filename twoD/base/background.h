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

#ifndef _TWODBACKGROUND_H_
#define _TWODBACKGROUND_H_

#include<allegro5/allegro.h>
#include "color.h"
#include "image.h"

class twoDBackground {
private:
	twoDImage *image; // background image
	twoDColor *color; // background color

public:
	twoDBackground(twoDImage*);
	twoDBackground(twoDColor*);
	twoDBackground(twoDColor*,twoDImage*);
	~twoDBackground();

	void draw();
	twoDColor* removeColor();
	twoDImage* removeImage();

	// setters	
	void setColor(twoDColor *c){ this->color = c; }
	void setImage(twoDImage *i){ this->image = i; }
};

#endif

