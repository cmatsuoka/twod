#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "../../twoD/objects/object.h"
#include "../../twoD/base/sprite.h"
#include "../../twoD/base/movement.h"

#include<string>
using namespace std;

#define CHARACTER_SPEED 200
#define CHARACTER_SPEED_RUN 300

#define CHARACTER_SPRITE_SPEED 25
#define CHARACTER_SPRITE_SPEED_RUN 35

#define CHARACTER_SPRITE_WIDTH 64
#define CHARACTER_SPRITE_HEIGHT 64

#define CHARACTER_LEFT_SPRITE string("resources/sprite/char_left.sprite")
#define CHARACTER_RIGHT_SPRITE string("resources/sprite/char_right.sprite")

class Character: public twoDObject {
	twoDSprite *leftSprite;
	twoDSprite *rightSprite;
	twoDSprite *last;

public:
	Character();
	~Character();
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*,int);
	void updatePosition();
};

#endif

