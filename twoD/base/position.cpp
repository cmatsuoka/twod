#include "position.h"

twoDPosition::twoDPosition(int x, int y){
	this->x = x;
	this->y = y;
}

twoDPosition::~twoDPosition(){

}

int twoDPosition::getX(){
	return this->x;
}

int twoDPosition::getY(){
	return this->y;
}

void twoDPosition::setX(int x){
	this->x = x;
}

void twoDPosition::setY(int y){
	this->y = y;
}

void twoDPosition::moveX(int offset){
	this->x += offset;
}

void twoDPosition::moveY(int offset){
	this->y += offset;
}


