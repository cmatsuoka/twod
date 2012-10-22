#include "background.h"

twoDBackground::twoDBackground(twoDImage *image){
	this->image = image;
	this->color = NULL;
}

twoDBackground::twoDBackground(twoDColor *color){
	this->color = color;
	this->image = NULL;
}

twoDBackground::twoDBackground(twoDColor *color, twoDImage *image){
	this->image = image;
	this->color = color;
}

twoDBackground::~twoDBackground(){
}

void twoDBackground::draw(){
	if(this->color != NULL)
		al_clear_to_color(this->color->map());
	if(this->image != NULL)
		this->image->draw();
}

twoDColor* twoDBackground::removeColor(){
	twoDColor *tmp;
	tmp = this->color;
	this->color = NULL;
	return tmp;
}

twoDImage* twoDBackground::removeImage(){
	twoDImage *tmp;
	tmp = this->image;
	this->image = NULL;
	return tmp;
}

