#include<string>
using namespace std;

#include "twoD/engine.h"
#include "twoD/base/sprite.h"
#include "twoD/base/text.h"

#include "test.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

#define SPRITE_PATH string("resources/sprite/")
#define SOUND_PATH string("resources/sound/")
#define IMG_PATH string("resources/img/")
#define FONT_PATH string("resources/font/")

#define CAT_SPRITE (SPRITE_PATH + string("cat.sprite"))
#define CAT_RUNNING_SPRITE (SPRITE_PATH + string("cat_running.sprite"))
#define DRAGON_SPRITE (SPRITE_PATH + string("dragon.sprite"))

#define TEXT_FONT (FONT_PATH + string("default.ttf"))
#define TEXT_SIZE 14
#define DRAGON_TEXT string("Dragon")
#define CAT_TEXT string("Cat")

#define CAT_SOUND (SOUND_PATH + string("meaw.wav"))

int main(int argc, char *argv[]){
	twoDEngine *engine;
	twoDObject *cat;
	twoDObject *catRun;
	twoDObject *dragon;
	twoDText *textCat, *textDragon;
   	
	engine = new twoDEngine(DISPLAY_WIDTH,DISPLAY_HEIGHT);

	textCat = new twoDText(TEXT_FONT, TEXT_SIZE);
	textCat->setColor(new twoDColor("white"));
	textCat->setText(CAT_TEXT);

	textDragon = new twoDText(TEXT_FONT, TEXT_SIZE);
	textDragon->setColor(new twoDColor("white"));
	textDragon->setText(DRAGON_TEXT);

	cat = (twoDObject*)new twoDTest(new twoDSprite(CAT_SPRITE), textCat, 20, 20, "");
	catRun = (twoDObject*)new twoDTest(new twoDSprite(CAT_RUNNING_SPRITE), textCat, 162, 100, CAT_SOUND);
	dragon = (twoDObject*)new twoDTest(new twoDSprite(DRAGON_SPRITE), textDragon, 300, 100, "");

	cat->setVisible(false);
	engine->addObject(cat,5);
	engine->addObject(catRun,5);
	engine->addObject(dragon,5);
	engine->main();

	return 0;
}

