#ifndef TWODCOLOR_H
#define TWODCOLOR_H

#include<allegro5/allegro.h>
#include<string>
using namespace std;

class twoDColor {
private:
	// RGB
	int red;
	int green;
	int blue;

public:
	twoDColor(int red, int green, int blue);
	twoDColor(string id); // preset colors
	~twoDColor();

	ALLEGRO_COLOR map();

};

#endif
