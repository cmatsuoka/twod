#ifndef _TWODWALL_H_
#define _TWODWALL_H_

#include<string>
using namespace std;

#include "../../twoD/objects/object.h"
#include "../../twoD/base/image.h"

class twoDWall: public twoDObject {
	twoDImage *image;
	int repeat;

public:
	twoDWall(string, int, int, int);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*,int);
	void updatePosition(int, int);
};

#endif

