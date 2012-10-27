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
	this->primitive = new twoDPrimitive();

	int wallX, wallY, wallW, wallH;
	wallX = x - 10;
	wallY = y - 10;
	wallW = this->width+10;
	wallH = this->height+10;

	this->primitive->addVertex(wallX,wallY,0,0);
	this->primitive->addVertex(wallX+wallW,wallY,100,0);
	this->primitive->addVertex(wallX+wallW,wallY+wallH,100,100);
	this->primitive->addVertex(wallX,wallY+wallH,0,100);
	this->primitive->setTexture("resources/img/wall.png");
	this->primitive->setType(TWOD_PRIMITIVE_TRIANGLE_FAN);
}

void twoDTest::draw(){
	if(this->visible){
		this->primitive->draw();
		this->sprite->draw();
		this->text->draw();
	}
}

void twoDTest::update(twoDEngine *engine){
	int textX, textY;
	int moveX, moveY;

	moveX = 0;
	moveY = 0;

	if(engine->keyPressed(KEY_UP))
		moveY = -10;
	if(engine->keyPressed(KEY_DOWN))
		moveY = 10;
	if(engine->keyPressed(KEY_LEFT))
		moveX = -10;
	if(engine->keyPressed(KEY_RIGHT))
		moveX = 10;
	if(engine->keyPressed(KEY_SPACE))
		if(this->sound != NULL)
			this->sound->play();

	this->x += moveX;
	this->y += moveY;
	this->primitive->move(moveX,moveY);

	textX = this->x + (this->width / 2);
	textY = this->y + ((this-> height - this->text->getSize()) / 2);

	this->sprite->setPosition(this->x, this->y);
	this->text->setPosition(textX, textY);
}

void twoDTest::collision(twoDObject *obj){
}

