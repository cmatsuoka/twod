#include<string>
#include<iostream>
using namespace std;

#include "../../twoD/engine.h"
#include "../../twoD/base/image.h"
#include "../../twoD/objects/map.h"
#include "ctrl_square.h"
#include "info.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

#define IMG_BG string("resources/img/bg.png")
#define IMG_MG string("resources/img/mg.png")
#define IMG_FG string("resources/img/fg.png")

#define BG_LAYER 5
#define MG_LAYER 15
#define FG_LAYER 25

#define SQUARE_SIZE 20
#define SQUARE_X 190
#define SQUARE_Y 290
#define SQUARE_LAYER MG_LAYER

#define INFO_TEXT string("A: increase speed     S: decrease speed     SPACE: stop     ARROWS: move")
#define INFO_X 10
#define INFO_Y 580
#define INFO_LAYER 28

// moving square example
int main(int argc, char *argv[]){
	twoDEngine *engine;
	twoDMap *bg, *mg, *fg;
	controlledSquare *square;
	infoWindow *info;

	engine = new twoDEngine(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	square = new controlledSquare(SQUARE_SIZE, new twoDColor("blue"));
	square->setInitialPosition(SQUARE_X,SQUARE_Y);

	info = new infoWindow(INFO_TEXT, INFO_X, INFO_Y);

	bg = new twoDMap();
	bg->setImage(new twoDImage(IMG_BG));
	bg->setParallax(true);
	bg->setRepeat(true);
	bg->setScroll(true);

	mg = new twoDMap();
	mg->setImage(new twoDImage(IMG_MG));
	mg->setParallax(true);
	mg->setRepeat(true);
	mg->setScroll(true);

	fg = new twoDMap();
	fg->setImage(new twoDImage(IMG_FG));
	fg->setParallax(true);
	fg->setRepeat(true);
	fg->setScroll(true);

	engine->addMainObject((twoDObject*)square, SQUARE_LAYER);

	engine->addObject((twoDObject*)info,INFO_LAYER);
	engine->addObject((twoDObject*)bg,BG_LAYER);
	engine->addObject((twoDObject*)mg,MG_LAYER);
	engine->addObject((twoDObject*)fg,FG_LAYER);

	engine->main();

	return 0;
}

