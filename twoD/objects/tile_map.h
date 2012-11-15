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

#ifndef _TWODTILEMAP_H_
#define _TWODTILEMAP_H_

#include<list>
using namespace std;

#include "object.h"
#include "../base/image.h"

#define DEFAULT_PARALLAX_MULTIPLIER 10
#define DEFAULT_SCROLL_SPEED 10

class twoDTileMap: public twoDObject {
	list<twoDImage*> tiles;
	bool scroll = false;
	bool parallax = false;
	bool repeat = false;
	int parallaxMultiplier = DEFAULT_PARALLAX_MULTIPLIER;

public:
	twoDTileMap();
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*,int);
	void updatePosition();

	void addTile(twoDImage*);
	void addTile(twoDImage*, int, int);

	// setters
	void setScroll(bool s){ this->scroll = s; }
	void setParallax(bool p){ this->parallax = p; }
	void setParallaxMultiplier(int m){ this->parallaxMultiplier = m; }
	void setRepeat(bool r){ this->repeat = r; }
};

#endif

