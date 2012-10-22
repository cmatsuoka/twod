#include "color.h"

twoDColor::twoDColor(int red, int green, int blue){
	this->red = red;
	this->green = green;
	this->blue = blue;
}

twoDColor::~twoDColor(){
}

twoDColor::twoDColor(string id){
	this->red = 0;
	this->green = 0;
	this->blue = 0;

	if(id == "red")
		this->red = 255;
	else if(id == "green")
		this->green = 255;
	else if(id == "blue")
		this->blue = 255;
	else if(id == "white"){
		this->red = 255;
		this->green = 255;
		this->blue = 255;
	}
}

ALLEGRO_COLOR twoDColor::map(){
	return al_map_rgb(this->red, this->green, this->blue);
}

