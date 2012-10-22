#ifndef TWODTEST_H
#define TWODTEST_H

#include "object.h"
#include "../base/sprite.h"

class twoDTest: public twoDObject {
	twoDSprite *sprite;

public:
	twoDTest(twoDSprite*, twoDPosition*);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*);
};

#endif

