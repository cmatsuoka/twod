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

