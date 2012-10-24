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

