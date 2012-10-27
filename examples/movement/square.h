#ifndef _TWODSQUARE_H_
#define _TWODSQUARE_H_

#include "../../twoD/objects/object.h"
#include "../../twoD/base/color.h"
#include "../../twoD/base/primitive.h"
#include "../../twoD/base/movement.h"

#define SPEED_STEP 1

class twoDSquare: public twoDObject {
	twoDPrimitive *primitive;
	twoDMovement *movement;

public:
	twoDSquare(int, twoDColor*);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*);
	void updatePosition(int, int);
};

#endif

