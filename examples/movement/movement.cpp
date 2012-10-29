#include<string>
using namespace std;

#include "../../twoD/engine.h"
#include "../../twoD/base/color.h"
#include "square.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

#define SQUARE_SIZE 20
#define SQUARE1_X 190
#define SQUARE1_Y 290
#define SQUARE2_X 590
#define SQUARE2_Y 290

// moving square example
int main(int argc, char *argv[]){
	twoDEngine *engine;
	twoDSquare *square1, *square2;
   	
	engine = new twoDEngine(DISPLAY_WIDTH,DISPLAY_HEIGHT);

	square1 = new twoDSquare(SQUARE_SIZE, new twoDColor("blue"));
	square1->setPosition(SQUARE1_X,SQUARE1_Y);
	square1->getMovement()->setDirection(TWOD_MOVE_DIRECTION_E);

	square2 = new twoDSquare(SQUARE_SIZE, new twoDColor("red"));
	square2->setPosition(SQUARE2_X,SQUARE2_Y);
	square2->getMovement()->setDirection(TWOD_MOVE_DIRECTION_W);

	engine->addObject((twoDObject*)square1,5);
	engine->addObject((twoDObject*)square2,5);
	engine->main();

	return 0;
}

