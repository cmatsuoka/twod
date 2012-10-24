#include "image.h"

static bool ALLEGRO_IMAGE_ADDON_INIT = false;

twoDImage::~twoDImage(){
	al_destroy_bitmap(this->bitmap);
}

twoDImage::twoDImage(string imgfile){
	int w, h;

	if(!ALLEGRO_IMAGE_ADDON_INIT){
		al_init_image_addon();
		ALLEGRO_IMAGE_ADDON_INIT = true;
	}

	this->bitmap = al_load_bitmap(imgfile.c_str());
	w = al_get_bitmap_width(this->bitmap);
	h = al_get_bitmap_height(this->bitmap);

	this->x = 0;
	this->y = 0;
	this->width = w;
	this->height = h;
}

twoDImage::twoDImage(ALLEGRO_BITMAP *bitmap){
	int w, h;

	this->bitmap = al_clone_bitmap(bitmap);
	w = al_get_bitmap_width(this->bitmap);
	h = al_get_bitmap_height(this->bitmap);

	this->x = 0;
	this->y = 0;
	this->width = w;
	this->height = h;
}

void twoDImage::draw(){
	int w, h;
	w = al_get_bitmap_width(this->bitmap);
	h = al_get_bitmap_height(this->bitmap);

	if((this->width == w) && (this->height == h))
		al_draw_bitmap(this->bitmap, this->x, this->y, 0);
	else 
		al_draw_scaled_bitmap(this->bitmap, 0, 0, w, h, this->x, this->y, this->width, this->height, 0);
}

void twoDImage::setSize(int dw, int dh){
	int sw, sh;
	float ratio = 0;
	sw = this->width;
	sh = this->height;

	if(dw == 0){
		ratio = (float)dh/sh;
		dw = sw*ratio;
	}
	else if(dh == 0){
		ratio = (float)dw/sw;
		dh = sh*ratio;
	}
	else
		ratio = 1;
	if(ratio == 0){
		dw = sw;
		dh = sh;
	}

	this->width = dw;
	this->height = dh;
}

void twoDImage::setAlpha(twoDColor *color){
	al_convert_mask_to_alpha(this->bitmap, color->map());
}

twoDImage * twoDImage::subImage(int x, int y, int w, int h){
	return new twoDImage(al_create_sub_bitmap(this->bitmap, x, y, w, h));
}

