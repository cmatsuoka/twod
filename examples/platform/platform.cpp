#include<string>
using namespace std;

#include "../../twoD/engine.h"
#include "../../twoD/base/color.h"
#include "../../twoD/base/text.h"
#include "../../twoD/objects/border.h"
#include "character.h"
#include "wall.h"
#include "info.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

#define CHARACTER_X 20
#define CHARACTER_Y 10

#define FLOOR_X 1
#define FLOOR_Y 500
#define FLOOR_REPEAT_IMG 80

#define PLATFORM_X 200
#define PLATFORM_Y 400
#define PLATFORM_REPEAT_IMG 10

#define INFO_TEXT string("SPACE: jump     ARROWS: move      A: run")
#define INFO_X 10
#define INFO_Y 580

int main(int argc, char *argv[]){
	twoDEngine *engine;
	standingWall *platform;
	standingWall *floor;
	infoWindow *info;
	twoDBorder *border;
	Character *character;

	engine = new twoDEngine(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	// character
	character = new Character();
	character->setInitialPosition(CHARACTER_X,CHARACTER_Y);
	engine->addMainObject((twoDObject*)character, 5);

	// borders
	border = new twoDBorder(TWOD_BORDER_LEFT, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	engine->addObject((twoDObject*)border,5);
	border = new twoDBorder(TWOD_BORDER_RIGHT, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	engine->addObject((twoDObject*)border,5);
	border = new twoDBorder(TWOD_BORDER_TOP, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	engine->addObject((twoDObject*)border,5);
	border = new twoDBorder(TWOD_BORDER_BOTTOM, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	engine->addObject((twoDObject*)border,5);

	// info OSD
	info = new infoWindow(INFO_TEXT, INFO_X, INFO_Y);
	engine->addObject((twoDObject*)info,10);

	// floor and a platform
	platform = new standingWall(string("resources/img/wall_mini.png"), PLATFORM_X, PLATFORM_Y, PLATFORM_REPEAT_IMG); 
	platform->setPlatform(true);
	floor = new standingWall(string("resources/img/wall_mini.png"), FLOOR_X, FLOOR_Y, FLOOR_REPEAT_IMG); 
	engine->addObject((twoDObject*)platform,5);
	engine->addObject((twoDObject*)floor,5);

	// main loop
	engine->main();

	return 0;
}

