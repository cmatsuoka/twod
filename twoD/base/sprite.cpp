/*
 * twoD gaming engine
 * Copyright (C) 2012 Thiago Garrett
 *
 * twoD is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * twoD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with twoD. If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#include "sprite.h"

twoDSprite::~twoDSprite(){
	for(int i=0; i<this->numImg; i++)
		delete this->image[i];
}

// Format:
//
// NUM_FILES NUM_TOTAL_SUBIMGS SWITCH_RATE
// SPRITE_WIDTH SPRITE_HEIGHT
// ALPHA_R ALPHA_G ALPHA_B
// IMAGE_1_PATH
// NUMBER_OF_SUBIMGS
// SUBIMG_1_X SUBIMG_1_Y
// SUBIMG_2_X SUBIMG_2_Y
// IMAGE_2_PATH
// ...
twoDSprite::twoDSprite(string spritefile){
	fstream f;
	int numFiles, numImg, switchRate, x, y, w, h;
	int alphaR, alphaG, alphaB, k; 
	string imgfile;
	twoDImage **image;
	twoDImage *tmpImage;
	twoDColor *alpha;

	f.open(spritefile.c_str(), fstream::in);

	f >> numFiles >> numImg >> switchRate;
	f >> w >> h;
	f >> alphaR >> alphaG >> alphaB;

	alpha = new twoDColor(alphaR, alphaG, alphaB);

	image = new twoDImage*[numImg];
	k = 0;
	for(int i=0; i<numFiles; i++){
		int numSubImg;
		f >> imgfile;
		f >> numSubImg;
		tmpImage = new twoDImage(imgfile);
		for(int j=0; j<numSubImg; j++){
			f >> x >> y;
			image[k] = tmpImage->subImage(x, y, w, h);
			if(alphaR >= 0)
				image[k]->setAlpha(alpha);
			k++;
		}
		delete tmpImage;
	}

	f.close();

	delete alpha;

	this->x = 0;
	this->y = 0;
	this->width = w;
	this->height = h;
	this->image = image;
	this->numImg = numImg;
	this->switchRate = switchRate;
	this->imgCount = 0;
	this->switchCount = 0;
}

void twoDSprite::draw(){
	this->image[this->imgCount]->setPosition(this->x, this->y);
	this->image[this->imgCount]->draw();

	this->switchCount += (float)this->switchRate/TWOD_FPS;
	
	if(this->switchCount >= 1){
		this->switchCount = 0;
		this->imgCount = (this->imgCount + 1) % this->numImg;
	}
}

void twoDSprite::setSize(int w, int h){
	for(int i=0; i<this->numImg; i++)
		this->image[i]->setSize(w, h);
	this->width = w;
	this->height = h;
}

