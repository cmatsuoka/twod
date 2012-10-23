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
	int x, y;
	int width, height;
	int numImg;
	int switchRatio;
	int switchCount;
	int imgCount;

public:
	twoDSprite(string); // sprite definition file
	~twoDSprite();

	void draw(); // draw sprite

	// setters
	void setSize(int,int);
	void setPosition(int x, int y){ this->x = x; this->y = y; }
	void setSwitchRatio(int s){ this->switchRatio = s; }

	// getters
	int getX(){ return this->x; }
	int getY(){ return this->y; }
	int getWidth(){ return this->width; }
	int getHeight(){ return this->height; }
};

#endif

