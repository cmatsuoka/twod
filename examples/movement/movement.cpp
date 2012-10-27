#include<string>
using namespace std;

#include "../../twoD/engine.h"
#include "../../twoD/base/color.h"
#include "square.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

#define SQUARE_SIZE 20
#define SQUARE_X 390
#define SQUARE_Y 290

// moving square example
int main(int argc, char *argv[]){
	twoDEngine *engine;
	twoDSquare *square;
   	
	engine = new twoDEngine(DISPLAY_WIDTH,DISPLAY_HEIGHT);

	square = new twoDSquare(SQUARE_SIZE, new twoDColor("blue"));
	square->setPosition(SQUARE_X,SQUARE_Y);

	engine->addObject((twoDObject*)square,5);
	engine->main();

	return 0;
}

