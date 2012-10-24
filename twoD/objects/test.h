#ifndef TWODTEST_H
#define TWODTEST_H

#include "object.h"
#include "../base/sprite.h"
#include "../base/text.h"
#include "../base/sound.h"

class twoDTest: public twoDObject {
	twoDSprite *sprite;
	twoDText *text;
	twoDSound *sound;

public:
	twoDTest(twoDSprite*, twoDText*, int, int, string);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*);
};

#endif

