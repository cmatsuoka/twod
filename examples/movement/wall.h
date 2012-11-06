#ifndef _WALL_H_
#define _WALL_H_

#include<string>
using namespace std;

#include "../../twoD/objects/object.h"
#include "../../twoD/base/image.h"

class standingWall: public twoDObject {
	twoDImage *image;
	int repeat;

public:
	standingWall(string, int, int, int);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*,int);
	void updatePosition();
};

#endif

