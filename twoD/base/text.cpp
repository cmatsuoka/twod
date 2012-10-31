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

extern ALLEGRO_DISPLAY *TWOD_DISPLAY;

twoDText::twoDText(string fontfile, int size){
	this->text = "";
	this->size = size;
	this->align = TWOD_TEXT_ALIGN_LEFT;
	this->color = new twoDColor("black");
	this->x = 0;
	this->y = 0;
	this->buffer = NULL;

	if(!ALLEGRO_FONT_ADDON_INIT){
		al_init_font_addon();
		al_init_ttf_addon();
		ALLEGRO_FONT_ADDON_INIT = true;
	}

	this->font = al_load_font(fontfile.c_str(), size, 0);
	this->height = al_get_font_line_height(this->font);
	this->setText("");
}

twoDText::~twoDText(){
	al_destroy_font(this->font);
	al_destroy_bitmap(this->buffer);
}

void twoDText::draw(){
	al_draw_bitmap(this->buffer, this->x, this->y, 0);
}

void twoDText::setText(string text){
	// buffer transparency
	twoDColor *bufferAlpha;
	bufferAlpha = new twoDColor((this->color->getRed()+50) % 256, 0, 0);

	this->text = text;
	this->width = al_get_text_width(this->font, text.c_str());

	// create new buffer
	if(this->buffer != NULL)
		al_destroy_bitmap(this->buffer);
	this->buffer = al_create_bitmap(this->width, this->height);

	// draw text on buffer with transparency
	al_set_target_bitmap(this->buffer);
	al_clear_to_color(bufferAlpha->map());
	al_convert_mask_to_alpha(this->buffer, bufferAlpha->map());
	al_draw_text(this->font, this->color->map(), 0, 0, this->align, this->text.c_str());
	al_set_target_backbuffer(TWOD_DISPLAY);
}

