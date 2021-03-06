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

#ifndef _TWODBLOCK_H_
#define _TWODBLOCK_H_

#include "object.h"
#include "../base/image.h"

class twoDBlock: public twoDObject {
	twoDImage *tile;

public:
	twoDBlock(twoDImage*);
	twoDBlock(int, int);
	void draw();
	void update(twoDEngine*);
	void collision(twoDObject*,int);
	void updatePosition();
};

#endif

