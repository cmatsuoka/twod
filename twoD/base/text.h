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

#ifndef _TWODTEXT_H_
#define _TWODTEXT_H_

#include<string>
#include<allegro5/allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include "color.h"
using namespace std;

// align
#define TWOD_TEXT_ALIGN_LEFT ALLEGRO_ALIGN_LEFT
#define TWOD_TEXT_ALIGN_CENTER ALLEGRO_ALIGN_CENTRE
#define TWOD_TEXT_ALIGN_RIGHT ALLEGRO_ALIGN_RIGHT

class twoDText {
private:
	ALLEGRO_FONT *font;
	twoDColor *color;
	int x, y;
	int size;
	int align;
	string text;

public:
	twoDText(string, int);
	~twoDText();

	void draw();
	void move(int mx, int my){ this->x += mx; this->y += my; }

	// setters
	void setColor(twoDColor *c){ this->color = c; }
	void setText(string t){ this->text = t; }
	void setAlign(int a){ this->align = a; }
	void setPosition(int x, int y){ this->x = x; this->y = y; }

	// getters
	int getX(){ return this->x; }
	int getY(){ return this->y; }
	twoDColor * getColor(){ return this->color; }	
	string getText(){ return this->text; }
	int getAlign(){ return this->align; }
	int getSize(){ return this->size; }
};

#endif

