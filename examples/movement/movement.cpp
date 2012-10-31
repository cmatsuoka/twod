#include<string>
using namespace std;

#include "../../twoD/engine.h"
#include "../../twoD/base/color.h"
#include "../../twoD/base/text.h"
#include "ctrl_square.h"
#include "wall.h"
#include "info.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

#define SQUARE_SIZE 20
#define SQUARE1_X 190
#define SQUARE1_Y 290
#define SQUARE2_X 590
#define SQUARE2_Y 290

#define WALL_X 350
#define WALL_Y 200
#define WALL_REPEAT_IMG 2

#define INFO_TEXT string("A: increase speed     S: decrease speed     SPACE: stop     ARROWS: move")
#define INFO_X 10
#define INFO_Y 580

// moving square example
int main(int argc, char *argv[]){
	twoDEngine *engine;
	controlledSquare *square1, *square2;
	standingWall *wall;
	infoWindow *info;

	engine = new twoDEngine(DISPLAY_WIDTH,DISPLAY_HEIGHT);

	info = new infoWindow(INFO_TEXT, INFO_X, INFO_Y);

	square1 = new controlledSquare(SQUARE_SIZE, new twoDColor("blue"));
	square1->setPosition(SQUARE1_X,SQUARE1_Y);
	square1->getMovement()->setDirection(TWOD_MOVE_DIRECTION_E);

	square2 = new controlledSquare(SQUARE_SIZE, new twoDColor("red"));
	square2->setPosition(SQUARE2_X,SQUARE2_Y);
	square2->getMovement()->setDirection(TWOD_MOVE_DIRECTION_W);

	wall = new standingWall(string("resources/img/wall.png"), WALL_X, WALL_Y, WALL_REPEAT_IMG); 

	engine->addObject((twoDObject*)square1,5);
//	engine->addObject((twoDObject*)square2,5);
	engine->addObject((twoDObject*)wall,5);
	engine->addObject((twoDObject*)info,10);
	engine->main();

	return 0;
}

