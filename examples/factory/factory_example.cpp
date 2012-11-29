#include<string>
#include<map>
using namespace std;

#include "../../twoD/engine.h"
#include "obj_factory.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

#define CHARACTER_X 20
#define CHARACTER_Y 10

#define WALL_IMG "resources/img/wall_mini.png"

#define FLOOR_X 1
#define FLOOR_Y 500
#define FLOOR_REPEAT_IMG 80

#define PLATFORM_X 200
#define PLATFORM_Y 400
#define PLATFORM_REPEAT_IMG 10

#define INFO_TEXT "SPACE: jump     ARROWS: move      A: run"
#define INFO_X 10
#define INFO_Y 580

int main(int argc, char *argv[]){
	twoDEngine *engine;
	twoDObject *obj;
	objFactory *f;

	map<string, void*> objDescr;
	string name, img, msg;
	int x, y, layer, dw, dh, repeat;
	int borders[4] = {TWOD_BORDER_LEFT, TWOD_BORDER_RIGHT, TWOD_BORDER_TOP, TWOD_BORDER_BOTTOM};

	// Object Factory
	f = new objFactory();

	engine = new twoDEngine(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	// character
	name = "character";
	x = CHARACTER_X;
	y = CHARACTER_Y;
	layer = 5;
	objDescr["name"] = (void *) &name;
	objDescr["x"] = (void *) &x;
	objDescr["y"] = (void *) &y;
	objDescr["layer"] = (void *) &layer;
	obj = f->createObject(objDescr);
	engine->addMainObject(obj);
	
	
	// borders
	name = "border";
	dw = DISPLAY_WIDTH;
	dh = DISPLAY_HEIGHT;
	objDescr["name"] = (void *) &name;
	objDescr["displayWidth"] = (void *) &dw;
	objDescr["displayHeight"] = (void *) &dh;
	for(int i=0; i<4; i++){
		objDescr["border"] = (void *) &borders[i];
		obj = f->createObject(objDescr);
		engine->addObject(obj, 5);
	}

	// info OSD
	msg = INFO_TEXT;
	x = INFO_X;
	y = INFO_Y;
	name = "info";
	objDescr["name"] = (void *) &name;
	objDescr["x"] = (void *) &x;
	objDescr["y"] = (void *) &y;
	objDescr["text"] = (void *) &msg;
	obj = f->createObject(objDescr);
	engine->addObject(obj, 10);

	// floor
	img = WALL_IMG;
	repeat = FLOOR_REPEAT_IMG;
	name = "floor";
	x = FLOOR_X;
	y = FLOOR_Y;
	objDescr["name"] = (void *) &name;
	objDescr["x"] = (void *) &x;
	objDescr["y"] = (void *) &y;
	objDescr["repeat"] = (void *) &repeat;
	objDescr["image"] = (void *) &img;
	obj = f->createObject(objDescr);
	engine->addObject(obj, 5);

	// platform
	repeat = PLATFORM_REPEAT_IMG;
	name = "platform";
	x = PLATFORM_X;
	y = PLATFORM_Y;
	objDescr["name"] = (void *) &name;
	objDescr["x"] = (void *) &x;
	objDescr["y"] = (void *) &y;
	objDescr["repeat"] = (void *) &repeat;
	objDescr["image"] = (void *) &img;
	obj = f->createObject(objDescr);
	engine->addObject(obj, 5);

	// main loop
	engine->main();

	return 0;
}

