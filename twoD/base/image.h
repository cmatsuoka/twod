#ifndef _TWODIMAGE_H_
#define _TWODIMAGE_H_

#include<string>
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include "color.h"
using namespace std;

class twoDImage {
private:
	ALLEGRO_BITMAP *bitmap;
	int x, y;
	int width, height;

public:
	twoDImage(string); // get image from a file
	twoDImage(ALLEGRO_BITMAP *); // create image from a bitmap
	~twoDImage();

	twoDImage * subImage(int,int,int,int); // get a smaller region of the image
	void draw(); // draw image
	void move(int mx, int my){ this->x += mx; this->y += my; }

	// setters
	void setSize(int, int);
	void setPosition(int x, int y){ this->x = x; this->y = y; }
	void setAlpha(twoDColor*); // set color that will be transparent

	// getters
	int getX(){ return this->x; }
	int getY(){ return this->y; }
	int getWidth(){ return this->width; }
	int getHeight(){ return this->height; }
	ALLEGRO_BITMAP * getBitmap(){ return this->bitmap; }
};

#endif

