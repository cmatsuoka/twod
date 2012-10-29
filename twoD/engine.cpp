/*
 * twoD gaming engine
 * Copyright (C) 2012 Thiago Garrett
 *
 * twoD is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * twoD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with twoD. If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#include "engine.h"

twoDEngine::twoDEngine(int width, int height){
	this->displayWidth = width;
	this->displayHeight = height;

	this->background = new twoDBackground(new twoDColor("black"));;

	for(int i=0; i<TWOD_KEYS_COUNT; i++)
		this->key[i] = false;

	for(int i=0; i<TWOD_LAYERS; i++)
		for(int j=0; j<TWOD_OBJ_PER_LAYER; j++)
			this->layer[i][j] = NULL;

	this->end = false;

	al_init();
	al_install_keyboard();
}

twoDEngine::~twoDEngine(){
}

bool twoDEngine::keyPressed(int key){
	return this->key[key];
}

bool twoDEngine::addObject(twoDObject *obj, int layer){
	obj->setLayer(layer);
	return this->addObject(obj);
}

bool twoDEngine::addObject(twoDObject *obj){
	int layer = obj->getLayer();
	for(int i=0; i<TWOD_OBJ_PER_LAYER; i++)
		if(this->layer[layer][i] == NULL){
			this->layer[layer][i] = obj;
			return true;
		}
	return false;
}

void twoDEngine::checkLayerCollision(twoDObject *obj[], int num){
	int i,j;
	int obj1X, obj1Y, obj1W, obj1H;
	int obj2X, obj2Y, obj2W, obj2H;
	bool xCollision, yCollision;

	for(i=0; i<num; i++){
		xCollision = false;
		yCollision = false;
		for(j=i+1; j<num; j++){
			// check collision between objects 'i' and 'j'
			obj1X = obj[i]->getX();
			obj1Y = obj[i]->getY();
			obj1W = obj[i]->getWidth();
			obj1H = obj[i]->getHeight();
			obj2X = obj[j]->getX();
			obj2Y = obj[j]->getY();
			obj2W = obj[j]->getWidth();
			obj2H = obj[j]->getHeight();

			// X axis
			if((obj2X >= obj1X) && (obj2X <= (obj1X+obj1W-1)))
				xCollision = true;
			else if((obj1X >= obj2X) && (obj1X <= (obj2X+obj2W-1)))
				xCollision = true;
			
			// Y axis
			if((obj2Y >= obj1Y) && (obj2Y <= (obj1Y+obj1H-1)))
				yCollision = true;
			else if((obj1Y >= obj2Y) && (obj1Y <= (obj2Y+obj2H-1)))
				yCollision = true;

			if(xCollision && yCollision){
				obj[i]->collision(obj[j]);
				obj[j]->collision(obj[i]);
			}
		}
	}
}

void twoDEngine::main(){
	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *event_queue;
	bool draw;

	// create display, timer and event queue
	display = al_create_display(this->displayWidth, this->displayHeight);
	timer = al_create_timer(1.0 / TWOD_FPS);
	event_queue = al_create_event_queue();

	// register event sources in the queue
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	// start the main loop
	this->end = false;
	draw = true;
	al_start_timer(timer);
	while(! this->end){
		if(draw && al_is_event_queue_empty(event_queue)){
			if(this->background != NULL)
				this->background->draw();

			// draw all objects in layer order
			for(int i=0; i<TWOD_LAYERS; i++)
				for(int j=0; j<TWOD_OBJ_PER_LAYER; j++)
					if(this->layer[i][j] != NULL)
						this->layer[i][j]->draw();
					else
						break;

			al_flip_display();
			draw = false;
		}

		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		if(event.type == ALLEGRO_EVENT_TIMER){
			// update all objects in layer order
			int i,j;
			for(i=0; i<TWOD_LAYERS; i++){
				for(j=0; j<TWOD_OBJ_PER_LAYER; j++){
					if(this->layer[i][j] != NULL)
						this->layer[i][j]->update(this);
					else
						break;
				}
				this->checkLayerCollision(layer[i],j);
			}
			draw = true;
		}
		else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			this->end = true;
			break;
		}
		// key pressed
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(event.keyboard.keycode){
				CASE_KEY(UP, true);
				CASE_KEY(DOWN, true);
				CASE_KEY(LEFT, true);
				CASE_KEY(RIGHT, true);
				CASE_KEY(SPACE, true);
				CASE_KEY(ESCAPE, true);
				CASE_KEY(ENTER, true);
			}
		}
		// key released
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch(event.keyboard.keycode){
				CASE_KEY(UP, false);
				CASE_KEY(DOWN, false);
				CASE_KEY(LEFT, false);
				CASE_KEY(RIGHT, false);
				CASE_KEY(SPACE, false);
				CASE_KEY(ESCAPE, false);
				CASE_KEY(ENTER, false);
			}
		}

		// quit when ESC is pressed
		if(this->key[KEY_ESCAPE]){
			this->end = true;
			break;
		}
	}

	// finish
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
}

void twoDEngine::finish(){
	this->end = true;
}

