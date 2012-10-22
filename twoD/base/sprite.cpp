#include "sprite.h"

twoDSprite::~twoDSprite(){
	for(int i=0; i<this->numImg; i++)
		delete this->image[i];
	delete this->size;
}

// Format:
//
// NUM_FILES NUM_TOTAL_SUBIMGS SWITCH_RATIO
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
	int numFiles, numImg, switchRatio, x, y, w, h;
	int alphaR, alphaG, alphaB, k; 
	string imgfile;
	twoDImage **image;
	twoDImage *tmpImage;
	twoDSize *size;
	twoDColor *alpha;

	f.open(spritefile.c_str(), fstream::in);

	f >> numFiles >> numImg >> switchRatio;
	f >> w >> h;
	f >> alphaR >> alphaG >> alphaB;

	size = new twoDSize(w, h);
	alpha = new twoDColor(alphaR, alphaG, alphaB);

	image = (twoDImage**)malloc(sizeof(twoDImage*) * numImg);
	k = 0;
	for(int i=0; i<numFiles; i++){
		int numSubImg;
		f >> imgfile;
		f >> numSubImg;
		tmpImage = new twoDImage(imgfile);
		for(int j=0; j<numSubImg; j++){
			f >> x >> y;
			image[k] = tmpImage->subImage(new twoDPosition(x, y), size);
			if(alphaR >= 0)
				image[k]->setAlpha(alpha);
			k++;
		}
		delete tmpImage;
	}

	f.close();

	delete alpha;

	this->size = size;
	this->image = image;
	this->position = new twoDPosition(0, 0);
	this->numImg = numImg;
	this->switchRatio = switchRatio;
	this->switchCount = 0;
	this->imgCount = 0;
}

twoDPosition * twoDSprite::getPosition(){
	return this->position;
}

void twoDSprite::setPosition(twoDPosition *position){
	this->position = position;   
}

void twoDSprite::draw(){
	this->image[this->imgCount]->draw(this->position);

	this->switchCount++;
	if(this->switchCount == this->switchRatio){
		this->imgCount = (this->imgCount + 1) % this->numImg;
		this->switchCount = 0;
	}
}

void twoDSprite::draw(twoDPosition *position){
	this->setPosition(position);
	this->draw();
}

twoDSize* twoDSprite::getSize(){
	return this->size;
}

