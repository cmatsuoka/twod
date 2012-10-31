#ifndef _CTRLSQUARE_H_
#define _CTRLSQUARE_H_

#include "../../twoD/objects/object.h"
#include "../../twoD/base/color.h"
#include "../../twoD/base/primitive.h"
#include "../../twoD/base/movement.h"

#define SPEED_STEP 1

class controlledSquare: public twoDObject {
	twoDPrimitive *primitive;

public:
	controlledSquare(int, twoDColor*);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*,int);
	void updatePosition(int, int);
};

#endif

