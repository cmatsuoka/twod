#include "size.h"

twoDSize::twoDSize(int w, int h){
	this->width = w;
	this->height = h;
}

twoDSize::~twoDSize(){

}

int twoDSize::getWidth(){
	return this->width;
}

int twoDSize::getHeight(){
	return this->height;
}

void twoDSize::setWidth(int w){
	this->width = w;
}

void twoDSize::setHeight(int h){
	this->height = h;
}


