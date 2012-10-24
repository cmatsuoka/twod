#ifndef TWODSOUND_H
#define TWODSOUND_H

#include<string>
#include<allegro5/allegro.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
using namespace std;

#define TWOD_SOUND_RESERVED_SAMPLES 32

// modes
#define TWOD_SOUND_PLAYMODE_ONCE ALLEGRO_PLAYMODE_ONCE
#define TWOD_SOUND_PLAYMODE_LOOP ALLEGRO_PLAYMODE_LOOP

class twoDSound {
private:
	ALLEGRO_SAMPLE *sound;
	ALLEGRO_PLAYMODE mode; // play mode (once or loop)
	float gain; // relative volume. 1.0 is normal
	float pan; // 0.0 is centered, -1.0 left and 1.0 right
	float speed; // play speed. 1.0 is normal

public:
	twoDSound(string);
	~twoDSound();

	void play();

	// setters
	void setMode(ALLEGRO_PLAYMODE m){ this->mode = m; }
	void setGain(float g){ this->gain = g; }
	void setPan(float p){ this->pan = p; }
	void setSpeed(float s){ this->speed = s; }

	// getters
	int getMode(){ return this->mode; }
	float getGain(){ return this->gain; }
	float getPan(){ return this->pan; }
	float getSpeed(){ return this->speed; }
};

#endif

