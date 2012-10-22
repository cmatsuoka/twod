#ifndef TWODSPRITE_H
#define TWODSPRITE_H

#include<string>
#include<fstream>
#include "image.h"
#include "color.h"
using namespace std;

class twoDSprite {
private:
	twoDImage **image;
	twoDPosition *position;
	twoDSize *size;
	int numImg;
	int switchRatio;
	int switchCount;
	int imgCount;

public:
	twoDSprite(string); // sprite definition file
	~twoDSprite();

	void setPosition(twoDPosition*); // puts image in another position
	void setSwitchRatio(int);
	twoDPosition * getPosition();
	twoDSize* getSize();

	void draw(); // draw image
	void draw(twoDPosition*); // draw image in a new position
};

#endif

