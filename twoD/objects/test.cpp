#include "test.h"

twoDTest::twoDTest(twoDSprite *sprite, twoDPosition *position){
	this->sprite = sprite;
	this->position = position;
	this->visible = true;
	this->collidable = true;
	this->state = TWOD_STATE_STANDING;
	this->size = sprite->getSize();
}

void twoDTest::draw(){
	if(this->visible)
		this->sprite->draw(this->position);
}

void twoDTest::update(twoDEngine *engine){
	if(engine->keyPressed(KEY_UP))
		this->position->moveY(-10);
	if(engine->keyPressed(KEY_DOWN))
		this->position->moveY(10);
	if(engine->keyPressed(KEY_LEFT))
		this->position->moveX(-10);
	if(engine->keyPressed(KEY_RIGHT))
		this->position->moveX(10);
}

void twoDTest::collision(twoDObject *obj){
}

