#include<string>
using namespace std;

#include "twoD/engine.h"
#include "twoD/objects/test.h"
#include "twoD/base/position.h"
#include "twoD/base/sprite.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

#define SPRITE_PATH string("resources/sprite/")
#define SOUND_PATH string("resources/sound/")
#define IMG_PATH string("resources/img/")
#define FONT_PATH string("resources/font/")

#define CAT_SPRITE (SPRITE_PATH + string("cat.sprite"))
#define CAT_RUNNING_SPRITE (SPRITE_PATH + string("cat_running.sprite"))
#define DRAGON_SPRITE (SPRITE_PATH + string("dragon.sprite"))

int main(int argc, char *argv[]){
	twoDEngine *engine;
	twoDObject *cat;
	twoDObject *catRun;
	twoDObject *dragon;
   	
	engine = new twoDEngine(DISPLAY_WIDTH,DISPLAY_HEIGHT);

	cat = (twoDObject*)new twoDTest(new twoDSprite(CAT_SPRITE), new twoDPosition(20,20));
	catRun = (twoDObject*)new twoDTest(new twoDSprite(CAT_RUNNING_SPRITE), new twoDPosition(100,100));
	dragon = (twoDObject*)new twoDTest(new twoDSprite(DRAGON_SPRITE), new twoDPosition(300,100));

	cat->setVisible(false);
	engine->addObject(cat,5);
	engine->addObject(catRun,5);
	engine->addObject(dragon,5);
	engine->main();

	return 0;
}

