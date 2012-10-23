#ifndef TWODTEST_H
#define TWODTEST_H

#include "object.h"
#include "../base/sprite.h"
#include "../base/text.h"

class twoDTest: public twoDObject {
	twoDSprite *sprite;
	twoDText *text;

public:
	twoDTest(twoDSprite*, twoDText*, int, int);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*);
};

#endif

