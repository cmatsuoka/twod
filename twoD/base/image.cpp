#include "image.h"

twoDImage::~twoDImage(){
	al_destroy_bitmap(this->bitmap);
}

twoDImage::twoDImage(string imgfile){
	int w, h;

	al_init_image_addon();

	this->bitmap = al_load_bitmap(imgfile.c_str());
	this->position = new twoDPosition(0,0);

	w = al_get_bitmap_width(this->bitmap);
	h = al_get_bitmap_height(this->bitmap);
	this->size = new twoDSize(w,h);
	this->drawSize = NULL;
}

twoDImage::twoDImage(ALLEGRO_BITMAP *bitmap){
	int w, h;

	this->bitmap = al_clone_bitmap(bitmap);
	this->position = new twoDPosition(0,0);

	w = al_get_bitmap_width(this->bitmap);
	h = al_get_bitmap_height(this->bitmap);
	this->size = new twoDSize(w,h);
	this->drawSize = NULL;
}

twoDSize * twoDImage::getSize(){
	return this->size;
}

twoDPosition * twoDImage::getPosition(){
	return this->position;
}

void twoDImage::setPosition(twoDPosition *position){
	this->position = position;   
}

void twoDImage::draw(){
	int x, y;
	x = this->position->getX();
	y = this->position->getY();
	if(this->drawSize == NULL)
		al_draw_bitmap(this->bitmap, x, y, 0);
	else {
		int sw, sh, dw, dh;
		float ratio = 0;
		sw = this->size->getWidth();
		sh = this->size->getHeight();
		dw = this->drawSize->getWidth();
		dh = this->drawSize->getHeight();

		if(dw == 0){
			ratio = (float)dh/sh;
			dw = sw*ratio;
		}
		else if(dh == 0){
			ratio = (float)dw/sw;
			dh = sh*ratio;
		}
		if(ratio == 0){
			dw = sw;
			dh = sh;
		}

		al_draw_scaled_bitmap(this->bitmap, 0, 0, sw, sh, x, y, dw, dh, 0);
	}
}

void twoDImage::draw(twoDPosition *position){
	this->setPosition(position);
	this->draw();
}

void twoDImage::draw(twoDSize *size){
	this->setDrawSize(size);
	this->draw();
}

void twoDImage::draw(twoDPosition *position, twoDSize *size){
	this->setPosition(position);
	this->setDrawSize(size);
	this->draw();
}

void twoDImage::setAlpha(twoDColor *color){
	al_convert_mask_to_alpha(this->bitmap, color->map());
}

void twoDImage::setDrawSize(twoDSize *size){
	this->drawSize = size;
} 

twoDImage * twoDImage::subImage(twoDPosition *position, twoDSize *size){
	int x, y, w, h;

	x = position->getX();
	y = position->getY();
	w = size->getWidth();
	h = size->getHeight();
	return new twoDImage(al_create_sub_bitmap(this->bitmap, x, y, w, h));
}

