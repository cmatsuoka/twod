#include "obj_factory.h"

objFactory::objFactory(){
}

twoDObject * objFactory::createObject(map<string, void *> descr){
	string name;
	name = *(string *) descr["name"];

	// create Character
	if(name == "character"){
		Character *c;
		int x, y, layer;

		x = *(int *) descr["x"];
		y = *(int *) descr["y"];
		layer = *(int *) descr["layer"];

		c = new Character();
		c->setInitialPosition(x, y);
		c->setLayer(layer);

		return (twoDObject *) c;
	}

	// create info
	if(name == "info"){
		infoWindow *i;
		int x, y;
		string text;
		
		x = *(int *) descr["x"];
		y = *(int *) descr["y"];
		text = *(string *) descr["text"];

		i = new infoWindow(text, x, y);
		return (twoDObject *) i;
	}

	// create platform
	if(name == "platform"){
		standingWall *w;
		int x, y, repeat;
		string img;
		
		x = *(int *) descr["x"];
		y = *(int *) descr["y"];
		repeat = *(int *) descr["repeat"];
		img = *(string *) descr["image"];

		w = new standingWall(img, x, y, repeat);
		w->setPlatform(true);
		return (twoDObject *) w;
	}

	// create floor
	if(name == "floor"){
		standingWall *w;
		int x, y, repeat;
		string img;
		
		x = *(int *) descr["x"];
		y = *(int *) descr["y"];
		repeat = *(int *) descr["repeat"];
		img = *(string *) descr["image"];

		w = new standingWall(img, x, y, repeat);
		return (twoDObject *) w;
	}

	// create border
	if(name == "border"){
		twoDBorder *b;
		int dw, dh, border;

		border = *(int *) descr["border"];
		dw = *(int *) descr["displayWidth"];
		dh = *(int *) descr["displayHeight"];

		b = new twoDBorder(border, dw, dh);
		return (twoDObject *) b;
	}

	return NULL;
}

