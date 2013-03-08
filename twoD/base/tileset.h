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

#ifndef _TWODTILESET_H_
#define _TWODTILESET_H_

#include<string>
#include "image.h"

class twoDTileset {
private:
	int tileWidth = 0;
	int tileHeight = 0;
	int spacing = 0;
	int firstID = 0;
	int numTiles = 0;
	twoDImage *tileset;
	twoDImage **tile;

public:
	twoDTileset(string, int, int, int, int, twoDColor*);
	~twoDTileset();

	twoDImage * getTile(int);
};

#endif

