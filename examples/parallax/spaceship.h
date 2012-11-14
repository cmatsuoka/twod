#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_

#include "../../twoD/objects/object.h"
#include "../../twoD/base/image.h"
#include "../../twoD/base/movement.h"

#define SPEED_STEP 10
#define SPACESHIP_IMAGE "resources/img/spaceship.bmp"

class spaceShip: public twoDObject {
	twoDImage *image;

public:
	spaceShip();
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*,int);
	void updatePosition();
};

#endif

