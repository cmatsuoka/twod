#include "test.h"

twoDTest::twoDTest(twoDSprite *sprite, twoDText *text, int x, int y, string soundfile){
	this->sprite = sprite;
	this->text = text;
	this->text->setAlign(TWOD_TEXT_ALIGN_CENTER);
	this->x = x;
	this->y = y;
	this->width = sprite->getWidth();
	this->height = sprite->getHeight();
	this->visible = true;
	this->collidable = true;
	this->state = TWOD_STATE_STANDING;
	if(soundfile != "")
		this->sound = new twoDSound(soundfile);
	else
		this->sound = NULL;
}

void twoDTest::draw(){
	if(this->visible){
		this->sprite->draw();
		this->text->draw();
	}
}

void twoDTest::update(twoDEngine *engine){
	int textX, textY;

	if(engine->keyPressed(KEY_UP))
		this->y += -10;
	if(engine->keyPressed(KEY_DOWN))
		this->y += 10;
	if(engine->keyPressed(KEY_LEFT))
		this->x += -10;
	if(engine->keyPressed(KEY_RIGHT))
		this->x += 10;
	if(engine->keyPressed(KEY_SPACE))
		if(this->sound != NULL)
			this->sound->play();

	textX = this->x + (this->width / 2);
	textY = this->y + ((this-> height - this->text->getSize()) / 2);

	this->sprite->setPosition(this->x, this->y);
	this->text->setPosition(textX, textY);
}

void twoDTest::collision(twoDObject *obj){
}

