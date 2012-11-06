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

#define TWOD_LAYERS 16
#define TWOD_OBJ_PER_LAYER 16

// FPS
const int TWOD_FPS = 60;

enum TWOD_KEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ESCAPE, KEY_ENTER,
	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K,
	KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, 
	KEY_X, KEY_W, KEY_Y, KEY_Z, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6,
	KEY_7, KEY_8, KEY_9,
	TWOD_KEYS_COUNT
};

// macro for keyboard keys handling 
#define CASE_KEY(NAME, VALUE) case ALLEGRO_KEY_##NAME: this->key[KEY_##NAME] = (VALUE); break

// collision positions
#define TWOD_POSITION_TOPLEFT 0
#define TWOD_POSITION_TOP 1
#define TWOD_POSITION_TOPRIGHT 2
#define TWOD_POSITION_LEFT 3
#define TWOD_POSITION_RIGHT 4
#define TWOD_POSITION_BOTLEFT 5
#define TWOD_POSITION_BOT 6
#define TWOD_POSITION_BOTRIGHT 7
#define TWOD_POSITION_INSIDE 8

class twoDEngine {
private:
	int displayWidth;
	int displayHeight;
	bool key[TWOD_KEYS_COUNT];
	bool end;
	twoDBackground *background;
	twoDObject *layer[TWOD_LAYERS][TWOD_OBJ_PER_LAYER];

	// collision
	void checkLayerCollision(twoDObject**,int); 
	int getCollisionPosition(twoDObject*, twoDObject*);
	void autoFixCollision(twoDObject*, twoDObject*, int);

public:
	twoDEngine(int width, int height);
	~twoDEngine();
	void main();
	void finish();
	bool keyPressed(int);
	bool addObject(twoDObject *);
	bool addObject(twoDObject *, int);
//	twoDObject* removeObject(twoDObject *); TODO

	// setters
	void setBackground(twoDBackground *b){ this->background = b; }
};

#endif

