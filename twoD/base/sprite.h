#ifndef _TWODSPRITE_H_
#define _TWODSPRITE_H_

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
	void move(int mx, int my){ this->x += mx; this->y += my; }

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

