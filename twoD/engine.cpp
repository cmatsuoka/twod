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

ALLEGRO_DISPLAY *TWOD_DISPLAY;

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
	int i, j, pos;
	int obj1X, obj1Y, obj1W, obj1H;
	int obj2X, obj2Y, obj2W, obj2H;
	bool xCollision, yCollision;

	for(i=0; i<num; i++){
		if(! obj[i]->isCollidable())
			continue;
		for(j=i+1; j<num; j++){
			if(! obj[j]->isCollidable())
				continue;
	
			xCollision = false;
			yCollision = false;

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
				pos = this->getCollisionPosition(obj[i],obj[j]);
				obj[i]->collision(obj[j], pos);
				pos = this->getCollisionPosition(obj[j],obj[i]);
				obj[j]->collision(obj[i], pos);
			}
		}
	}
}

int twoDEngine::getCollisionPosition(twoDObject *obj1, twoDObject *obj2){
	int position = 0;

	int obj1X1, obj1X2, obj1X3, obj1X4;
	int obj1Y1, obj1Y2, obj1Y3, obj1Y4;
	int obj2X1, obj2X2, obj2X3, obj2X4;
	int	obj2Y1, obj2Y2, obj2Y3, obj2Y4;

	obj1X1 = obj1X3 = obj1->getX();
	obj1Y1 = obj1Y2 = obj1->getY();
	obj1X2 = obj1X4 = obj1->getX() + obj1->getWidth() - 1;
	obj1Y3 = obj1Y4 = obj1->getY() + obj1->getHeight() - 1;
	
	obj2X1 = obj2X3 = obj2->getX();
	obj2Y1 = obj2Y2 = obj2->getY();
	obj2X2 = obj2X4 = obj2->getX() + obj2->getWidth() - 1;
	obj2Y3 = obj2Y4 = obj2->getY() + obj2->getHeight() - 1;

	// position top left
	if((obj1X1 < obj2X1) && (obj1Y1 < obj2Y1)){
		position = TWOD_POSITION_TOPLEFT;
	}
	// position top
	else if((obj1Y1 < obj2Y1) && (obj1X1 >= obj2X1) && (obj1X2 <= obj2X2)){
		position = TWOD_POSITION_TOP;
	}
	// position top right
	else if((obj1X2 > obj2X2) && (obj1Y1 < obj2Y1)){
		position = TWOD_POSITION_TOPRIGHT;
	}
	// position left
	else if((obj1X1 < obj2X1) && (obj1Y1 >= obj2Y1) && (obj1Y3 <= obj2Y3)){
		position = TWOD_POSITION_LEFT;
	}
	// position right
	else if((obj1X2 > obj2X2) && (obj1Y1 >= obj2Y1) && (obj1Y3 <= obj2Y4)){
		position = TWOD_POSITION_RIGHT;
	}
	// position bot left
	else if((obj1X1 < obj2X1) && (obj1Y3 > obj2Y3)){
		position = TWOD_POSITION_BOTLEFT;
	}
	// position bot 
	else if((obj1Y3 > obj2Y3) && (obj1X3 >= obj2X3) && (obj1X4 <= obj2X4)){
		position = TWOD_POSITION_BOT;
	}
	// position bot right
	else if((obj1X4 > obj2X4) && (obj1Y4 < obj2Y4)){
		position = TWOD_POSITION_BOTRIGHT;
	}

	return position;
}


void twoDEngine::main(){
	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *event_queue;
	bool draw;

	// create display, timer and event queue
	display = al_create_display(this->displayWidth, this->displayHeight);
	TWOD_DISPLAY = display;
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
					if(this->layer[i][j] != NULL){
						if(this->layer[i][j]->isVisible())
							this->layer[i][j]->draw();
					}
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
				CASE_KEY(A, true);
				CASE_KEY(B, true);
				CASE_KEY(C, true);
				CASE_KEY(D, true);
				CASE_KEY(E, true);
				CASE_KEY(F, true);
				CASE_KEY(G, true);
				CASE_KEY(H, true);
				CASE_KEY(I, true);
				CASE_KEY(J, true);
				CASE_KEY(K, true);
				CASE_KEY(L, true);
				CASE_KEY(M, true);
				CASE_KEY(N, true);
				CASE_KEY(O, true);
				CASE_KEY(P, true);
				CASE_KEY(Q, true);
				CASE_KEY(R, true);
				CASE_KEY(S, true);
				CASE_KEY(T, true);
				CASE_KEY(U, true);
				CASE_KEY(V, true);
				CASE_KEY(X, true);
				CASE_KEY(W, true);
				CASE_KEY(Y, true);
				CASE_KEY(Z, true);
				CASE_KEY(0, true);
				CASE_KEY(1, true);
				CASE_KEY(2, true);
				CASE_KEY(3, true);
				CASE_KEY(4, true);
				CASE_KEY(5, true);
				CASE_KEY(6, true);
				CASE_KEY(7, true);
				CASE_KEY(8, true);
				CASE_KEY(9, true);
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
				CASE_KEY(A, false);
				CASE_KEY(B, false);
				CASE_KEY(C, false);
				CASE_KEY(D, false);
				CASE_KEY(E, false);
				CASE_KEY(F, false);
				CASE_KEY(G, false);
				CASE_KEY(H, false);
				CASE_KEY(I, false);
				CASE_KEY(J, false);
				CASE_KEY(K, false);
				CASE_KEY(L, false);
				CASE_KEY(M, false);
				CASE_KEY(N, false);
				CASE_KEY(O, false);
				CASE_KEY(P, false);
				CASE_KEY(Q, false);
				CASE_KEY(R, false);
				CASE_KEY(S, false);
				CASE_KEY(T, false);
				CASE_KEY(U, false);
				CASE_KEY(V, false);
				CASE_KEY(X, false);
				CASE_KEY(W, false);
				CASE_KEY(Y, false);
				CASE_KEY(Z, false);
				CASE_KEY(0, false);
				CASE_KEY(1, false);
				CASE_KEY(2, false);
				CASE_KEY(3, false);
				CASE_KEY(4, false);
				CASE_KEY(5, false);
				CASE_KEY(6, false);
				CASE_KEY(7, false);
				CASE_KEY(8, false);
				CASE_KEY(9, false);
			}
		}
	}

	// finish
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	TWOD_DISPLAY = NULL;
}

void twoDEngine::finish(){
	this->end = true;
}

