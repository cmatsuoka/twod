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

#include "sound.h"

static bool ALLEGRO_SOUND_ADDON_INIT = false;

twoDSound::twoDSound(string soundfile){
	if(!ALLEGRO_SOUND_ADDON_INIT){
		al_install_audio();
		al_init_acodec_addon();
		al_restore_default_mixer();
		al_reserve_samples(TWOD_SOUND_RESERVED_SAMPLES);
		ALLEGRO_SOUND_ADDON_INIT = true;
	}

	this->sound = al_load_sample(soundfile.c_str());
	this->mode = TWOD_SOUND_PLAYMODE_ONCE;
	this->gain = 1.0;
	this->pan = 0.0;
	this->speed = 1.0;
}

twoDSound::~twoDSound(){
	 al_destroy_sample(this->sound);
}

void twoDSound::play(){
	al_play_sample(this->sound, this->gain, this->pan, this->speed, this->mode, NULL);
}

