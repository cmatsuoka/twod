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

#ifndef _TWODENGINE_H_
#define _TWODENGINE_H_

// solve cross-reference
class twoDObject;

#include "objects/object.h"
#include "base/background.h"

// XXX DEBUG
#include<iostream>
using namespace std;
#define DEBUG(MSG) cout << (MSG) << endl

#define TWOD_FPS 30
#define TWOD_LAYERS 16
#define TWOD_OBJ_PER_LAYER 16

enum TWOD_KEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ESCAPE, KEY_ENTER,
	TWOD_KEYS_COUNT
};

// macro for keyboard keys handling 
#define CASE_KEY(NAME, VALUE) case ALLEGRO_KEY_##NAME: this->key[KEY_##NAME] = (VALUE); break

class twoDEngine {
private:
	ALLEGRO_DISPLAY *display;
	int displayWidth;
	int displayHeight;
	bool key[TWOD_KEYS_COUNT];
	bool end;
	twoDBackground *background;
	twoDObject *layer[TWOD_LAYERS][TWOD_OBJ_PER_LAYER];

public:
	twoDEngine(int width, int height);
	~twoDEngine();
	void main();
	void checkCollision(twoDObject*); 
	bool keyPressed(int);
	bool addObject(twoDObject *);
	bool addObject(twoDObject *, int);
// TODO	twoDObject* removeObject(twoDObject *);

	// setters
	void setBackground(twoDBackground *b){ this->background = b; }
};

#endif

