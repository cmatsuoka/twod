#ifndef _MVSQUARE_H_
#define _MVSQUARE_H_

#include "../../twoD/objects/object.h"
#include "../../twoD/base/color.h"
#include "../../twoD/base/primitive.h"
#include "../../twoD/base/movement.h"

class movingSquare: public twoDObject {
	twoDPrimitive *primitive;

public:
	movingSquare(int, twoDColor*);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*,int);
	void updatePosition();
};

#endif

