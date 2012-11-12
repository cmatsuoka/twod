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

// XXX for debugging
#include<iostream>
using namespace std;

// solve cross-reference
class twoDObject;

#include "objects/object.h"
#include "base/background.h"

#define TWOD_LAYERS 30
#define TWOD_OBJ_PER_LAYER 50

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
enum TWOD_POSITIONS {
	TWOD_POSITION_TOPLEFT,
	TWOD_POSITION_TOP,
	TWOD_POSITION_TOPRIGHT,
	TWOD_POSITION_LEFT,
	TWOD_POSITION_RIGHT,
	TWOD_POSITION_BOTLEFT,
	TWOD_POSITION_BOT,
	TWOD_POSITION_BOTRIGHT,
	TWOD_POSITION_INSIDE
};

class twoDEngine {
private:
	int displayWidth;
	int displayHeight;
	bool key[TWOD_KEYS_COUNT];
	bool end;
	twoDBackground *background;
	twoDObject *layer[TWOD_LAYERS][TWOD_OBJ_PER_LAYER];
	twoDObject *mainObject;

	// collision
	void checkLayerCollision(twoDObject**,int); 
	int getCollisionPosition(twoDObject*, twoDObject*);
	void autoFixCollision(twoDObject*, twoDObject*, int);
	void autoRedirectCollision(twoDObject*, twoDObject*, int);

public:
	twoDEngine(int width, int height);
	~twoDEngine();
	void main();
	void finish();
	bool keyPressed(int);
	bool addObject(twoDObject *);
	bool addObject(twoDObject *, int);
	twoDObject* removeObject(twoDObject *);
	bool addMainObject(twoDObject*);
	bool addMainObject(twoDObject *, int);

	// setters
	void setBackground(twoDBackground *b){ this->background = b; }

	// getters
	int getDisplayWidth(){ return this->displayWidth; };
	int getDisplayHeight(){ return this->displayHeight; };
	twoDObject * getMainObject(){ return this->mainObject; }
};

#endif

