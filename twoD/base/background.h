#ifndef _TWODBACKGROUND_H_
#define _TWODBACKGROUND_H_

#include<allegro5/allegro.h>
#include "color.h"
#include "image.h"

class twoDBackground {
private:
	twoDImage *image; // background image
	twoDColor *color; // background color

public:
	twoDBackground(twoDImage*);
	twoDBackground(twoDColor*);
	twoDBackground(twoDColor*,twoDImage*);
	~twoDBackground();

	void draw();
	twoDColor* removeColor();
	twoDImage* removeImage();

	// setters	
	void setColor(twoDColor *c){ this->color = c; }
	void setImage(twoDImage *i){ this->image = i; }
};

#endif

