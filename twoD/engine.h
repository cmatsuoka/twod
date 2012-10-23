// Very simple 2D gaming engine using Allegro 5
// Written by Thiago Garrett <thgarrett@gmail.com>
//
#ifndef TWODENGINE_H
#define TWODENGINE_H

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

