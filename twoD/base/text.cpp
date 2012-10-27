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

#include "text.h"

static bool ALLEGRO_FONT_ADDON_INIT = false;

twoDText::twoDText(string fontfile, int size){
	this->text = "";
	this->size = size;
	this->align = TWOD_TEXT_ALIGN_LEFT;
	this->color = new twoDColor("black");
	this->x = 0;
	this->y = 0;

	if(!ALLEGRO_FONT_ADDON_INIT){
		al_init_font_addon();
		al_init_ttf_addon();
		ALLEGRO_FONT_ADDON_INIT = true;
	}

	this->font = al_load_font(fontfile.c_str(), size, 0);
}

twoDText::~twoDText(){
	al_destroy_font(this->font);
}

void twoDText::draw(){
	al_draw_text(this->font, this->color->map(), this->x, this->y, this->align, this->text.c_str());
}

