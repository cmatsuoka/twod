#ifndef TWODIMAGE_H
#define TWODIMAGE_H

#include<string>
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include "position.h"
#include "size.h"
#include "color.h"
using namespace std;

class twoDImage {
private:
	ALLEGRO_BITMAP *bitmap;
	twoDPosition *position;
	twoDSize *size;
	twoDSize *drawSize;

public:
	twoDImage(string); // get image from a file
	twoDImage(ALLEGRO_BITMAP *); // create image from a bitmap
	~twoDImage();

	twoDImage * subImage(twoDPosition*, twoDSize*); // get a smaller region of the image
	twoDSize * getSize();
	twoDPosition * getPosition();

	void setPosition(twoDPosition*); // puts image in another position
	void setDrawSize(twoDSize*); // change draw size
	void setAlpha(twoDColor*); // set color the will be transparent

	void draw(); // draw image
	void draw(twoDPosition*); // draw image in a new position
	void draw(twoDSize*); // draw image with a new size
	void draw(twoDPosition*, twoDSize*); // draw image in a new position and with a new size
};

#endif

