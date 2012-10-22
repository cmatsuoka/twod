#ifndef TWODOBJECT_H
#define TWODOBJECT_H

// solve cross-reference
class twoDEngine;

#include "../engine.h"
#include "../base/position.h"
#include "../base/size.h"
//#include "../base/movement.h"

// objects states
#define TWOD_STATE_STANDING 1
#define TWOD_STATE_MOVING 2
#define TWOD_STATE_JUMPING 4
#define TWOD_STATE_COLLIDING 8

class twoDObject {
protected:
	int state;
	int layer;
	bool visible;
	bool collidable;

	twoDPosition *position;
	twoDSize *size;
//	twoDMovement *movement;

public:
	virtual void draw() = 0;
	virtual void update(twoDEngine*) = 0;
	virtual void collision(twoDObject*) = 0;

	// getters
	int getLayer(){ return this-> layer; }
	twoDPosition* getPosition(){ return this->position; }
	twoDSize* getSize(){ return this->size; }

	// setters
	void setLayer(int l){ this->layer = l; }
	void setVisible(bool v){ this->visible = v; }
	void setCollidable(bool c){ this->collidable = c; }
};

#endif

