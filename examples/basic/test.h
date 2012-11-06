#ifndef _TWODTEST_H_
#define _TWODTEST_H_

#include "../../twoD/objects/object.h"
#include "../../twoD/base/sprite.h"
#include "../../twoD/base/text.h"
#include "../../twoD/base/sound.h"
#include "../../twoD/base/primitive.h"

class twoDTest: public twoDObject {
	twoDSprite *sprite;
	twoDText *text;
	twoDSound *sound;
	twoDPrimitive *primitive;

public:
	twoDTest(twoDSprite*, twoDText*, int, int, string);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*,int);
	void updatePosition();
};

#endif

