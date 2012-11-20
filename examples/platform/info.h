#ifndef _INFO_H_
#define _INFO_H_

#include<string>
using namespace std;

#include "../../twoD/objects/object.h"
#include "../../twoD/base/primitive.h"
#include "../../twoD/base/text.h"

class infoWindow: public twoDObject {
	twoDText *text;

public:
	infoWindow(string, int, int);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*, int);
	void updatePosition();
};

#endif

