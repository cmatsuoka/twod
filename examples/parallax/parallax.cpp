#include<string>
#include<iostream>
using namespace std;

#include "../../twoD/engine.h"
#include "../../twoD/base/image.h"
#include "../../twoD/objects/image_map.h"
#include "spaceship.h"
#include "info.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

#define IMG_BG string("resources/img/bg.png")
#define IMG_MG string("resources/img/mg.png")
#define IMG_FG string("resources/img/fg.png")

#define BG_LAYER 5
#define MG_LAYER 15
#define FG_LAYER 25

#define SPACESHIP_X 190
#define SPACESHIP_Y 290
#define SPACESHIP_LAYER MG_LAYER

#define INFO_TEXT string("A: increase speed     S: decrease speed     SPACE: stop     ARROWS: move")
#define INFO_X 10
#define INFO_Y 580
#define INFO_LAYER 28

// spaceship with parallax background example
int main(int argc, char *argv[]){
	twoDEngine *engine;
	twoDImageMap *bg, *mg, *fg;
	spaceShip *spaceship;
	infoWindow *info;

	engine = new twoDEngine(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	spaceship = new spaceShip();
	spaceship->setInitialPosition(SPACESHIP_X,SPACESHIP_Y);

	info = new infoWindow(INFO_TEXT, INFO_X, INFO_Y);

	bg = new twoDImageMap();
	bg->setImage(new twoDImage(IMG_BG));
	bg->setParallax(true);
	bg->setRepeat(true);
	bg->setScroll(true);

	mg = new twoDImageMap();
	mg->setImage(new twoDImage(IMG_MG));
	mg->setParallax(true);
	mg->setRepeat(true);
	mg->setScroll(true);

	fg = new twoDImageMap();
	fg->setImage(new twoDImage(IMG_FG));
	fg->setParallax(true);
	fg->setRepeat(true);
	fg->setScroll(true);

	engine->addMainObject((twoDObject*)spaceship, SPACESHIP_LAYER);

	engine->addObject((twoDObject*)info,INFO_LAYER);
	engine->addObject((twoDObject*)bg,BG_LAYER);
	engine->addObject((twoDObject*)mg,MG_LAYER);
	engine->addObject((twoDObject*)fg,FG_LAYER);

	engine->main();

	return 0;
}

