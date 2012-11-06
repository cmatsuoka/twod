#include "info.h"

infoWindow::infoWindow(string text, int x, int y){
	this->text = new twoDText("resources/font/default.ttf", 14);
	this->text->setColor(new twoDColor("white"));
	this->text->setText(text);
	this->text->setPosition(x,y);

	this->x = x;
	this->y = y;
	this->width = this->text->getWidth();
	this->height = this->text->getHeight();;

	this->visible = true;
	this->collidable = false;
	this->layer = 10;
	this->state = TWOD_STATE_STANDING;
	this->movement = NULL;
}

void infoWindow::draw(){
	this->text->draw();
}

void infoWindow::update(twoDEngine *engine){
}

void infoWindow::collision(twoDObject *obj, int position){
}

void infoWindow::updatePosition(){
}

