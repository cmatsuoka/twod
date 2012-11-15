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

#include "tileset.h"

twoDTileset::~twoDTileset(){
	delete this->tileset;
	for(int i=0; i<this->numTiles; i++)
		if(this->tile[i] != NULL)
			delete this->tile[i];
}

twoDTileset::twoDTileset(string tilesetfile, int w, int h, int s, int id, twoDColor *alpha){
	int numX, numY, imgW, imgH;

	this->tileWidth = w;
	this->tileHeight = h;
	this->spacing = s;
	this->firstID = id;

	this->tileset = new twoDImage(tilesetfile);
	if(alpha != NULL)
		this->tileset->setAlpha(alpha);
	imgW = this->tileset->getWidth();
	imgH = this->tileset->getHeight();

	numX = (imgW + s) / (w + s);
	numY = (imgH + s) / (h + s);
	
	this->numTiles = numX * numY;
	this->tile = new twoDImage*[this->numTiles];
	for(int i=0; i<this->numTiles; i++)
		this->tile[i] = NULL;
}

twoDImage * twoDTileset::getTile(int x){
	int id;

	id = x - firstID;
	if(id < 0)
		return NULL;
	if(id >= this->numTiles)
		return NULL;

	if(tile[id] != NULL)
		return tile[id];
	else {
		int i, x, y, w, h, s, imgW;
		i = x = y = 0;
		w = this->tileWidth;
		h = this->tileHeight;
		s = this->spacing;
		imgW = this->tileset->getWidth();

		while(i != id){
			x = x + w + s;
			if(x >= imgW){
				x = 0;
				y = y + h + s;
			}

			i++;
		}

		this->tile[id] = this->tileset->subImage(x, y, w, h);
		return tile[id];
	}
}

