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
	this->mainObject = NULL;

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

bool twoDEngine::addMainObject(twoDObject *obj){
	if(this->mainObject != NULL)
		this->removeObject(this->mainObject);
	if(this->addObject(obj)){
		this->mainObject = obj;
		return true;
	}
	return false;
}

bool twoDEngine::addMainObject(twoDObject *obj, int layer){
	obj->setLayer(layer);
	return this->addMainObject(obj);
}

void twoDEngine::checkLayerCollision(twoDObject *obj[], int num){
	int i, j, pos1, pos2;
	int obj1X, obj1Y, obj1W, obj1H, oldObj1X, oldObj1Y;
	int obj2X, obj2Y, obj2W, obj2H;
	bool xCollision, yCollision;

	for(i=0; i<num; i++){
		if((! obj[i]->isCollidable()) || (! obj[i]->hasMoved()))
			continue;
		for(j=0; j<num; j++){
			if((! obj[j]->isCollidable()) || (i == j))
				continue;
	
			xCollision = false;
			yCollision = false;

			// check collision between objects 'i' and 'j'
			obj1X = obj[i]->getX();
			obj1Y = obj[i]->getY();
			obj1W = obj[i]->getWidth();
			obj1H = obj[i]->getHeight();
			oldObj1X = obj[i]->getOldX();
			oldObj1Y = obj[i]->getOldY();
			obj2X = obj[j]->getX();
			obj2Y = obj[j]->getY();
			obj2W = obj[j]->getWidth();
			obj2H = obj[j]->getHeight();

			// X axis
			if((obj2X >= obj1X) && (obj2X <= (obj1X+obj1W-1)))
				xCollision = true;
			else if((obj1X >= obj2X) && (obj1X <= (obj2X+obj2W-1)))
				xCollision = true;
			else if(((oldObj1X+obj1W-1) <= obj2X) && (obj1X > obj2X))
				xCollision = true;
			else if(((obj1X+obj1W-1) < (obj2X+obj2W-1)) && (oldObj1X >= (obj2X+obj2W-1)))
				xCollision = true;
			
			// Y axis
			if((obj2Y >= obj1Y) && (obj2Y <= (obj1Y+obj1H-1)))
				yCollision = true;
			else if((obj1Y >= obj2Y) && (obj1Y <= (obj2Y+obj2H-1)))
				yCollision = true;
			else if(((oldObj1Y+obj1H-1) <= obj2Y) && (obj1Y > obj2Y))
				yCollision = true;
			else if(((obj1Y+obj1H-1) < (obj2Y+obj2H-1)) && (obj1Y >= (obj2Y+obj2H-1)))
				yCollision = true;

			if(xCollision && yCollision){
				pos1 = this->getCollisionPosition(obj[i],obj[j]);
				pos2 = this->getCollisionPosition(obj[j],obj[i]);

				if(obj[i]->getAutoFixCollision())
					this->autoFixCollision(obj[i], obj[j], pos1);
				if(obj[i]->getAutoRedirectCollision())
					this->autoRedirectCollision(obj[i], obj[j], pos1);
				obj[i]->collision(obj[j], pos1);
				
				if(obj[j]->getAutoFixCollision())
					this->autoFixCollision(obj[j], obj[i], pos2);
				if(obj[j]->getAutoRedirectCollision())
					this->autoRedirectCollision(obj[j], obj[i], pos2);
				obj[j]->collision(obj[i], pos2);
			}
		}
	}
}

int twoDEngine::getCollisionPosition(twoDObject *obj1, twoDObject *obj2){
	int position = -1;

	int obj1X1, obj1X2, obj1X3, obj1X4;
	int oldObj1X1, oldObj1X2, oldObj1X3, oldObj1X4;
	int obj1Y1, obj1Y2, obj1Y3, obj1Y4;
	int oldObj1Y1, oldObj1Y2;
	int obj2X1, obj2X2, obj2X3, obj2X4;
	int	obj2Y1, obj2Y2, obj2Y3, obj2Y4;
	int obj1Dir;

	obj1X1 = obj1X3 = obj1->getX();
	obj1Y1 = obj1Y2 = obj1->getY();
	obj1X2 = obj1X4 = obj1->getX() + obj1->getWidth() - 1;
	obj1Y3 = obj1Y4 = obj1->getY() + obj1->getHeight() - 1;
	oldObj1X1 = oldObj1X3 = obj1->getOldX();
	oldObj1Y1 = oldObj1Y2 = obj1->getOldY();
	oldObj1X2 = oldObj1X4 = obj1->getOldX() + obj1->getWidth() - 1;
	
	obj2X1 = obj2X3 = obj2->getX();
	obj2Y1 = obj2Y2 = obj2->getY();
	obj2X2 = obj2X4 = obj2->getX() + obj2->getWidth() - 1;
	obj2Y3 = obj2Y4 = obj2->getY() + obj2->getHeight() - 1;

	if(obj1->getMovement() != NULL)
		obj1Dir = obj1->getMovement()->getDirection();
	else
		obj1Dir = -1;

	// position top left
	if((obj1X1 < obj2X1) && (obj1Y1 < obj2Y1)
		&& (obj1Dir != TWOD_MOVE_DIRECTION_W) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_NW) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_N)
		){
		position = TWOD_POSITION_TOPLEFT;
	}
	// position top
	else if((obj1Y1 < obj2Y1) && (obj1X1 >= obj2X1) && (obj1X2 <= obj2X2)
		&& (obj1Dir != TWOD_MOVE_DIRECTION_N) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_NW) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_NE)
		){
		position = TWOD_POSITION_TOP;
	}
	// position top right
	else if((obj1X2 > obj2X2) && (obj1Y1 < obj2Y1)
		&& (obj1Dir != TWOD_MOVE_DIRECTION_E) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_NE) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_N)
		){
		position = TWOD_POSITION_TOPRIGHT;
	}
	// position left
	else if((obj1X1 < obj2X1) && (obj1Y1 >= obj2Y1) && (obj1Y3 <= obj2Y3) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_W) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_SW) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_NW)
		){
		position = TWOD_POSITION_LEFT;
	}
	// position right
	else if((obj1X2 > obj2X2) && (obj1Y1 >= obj2Y1) && (obj1Y3 <= obj2Y4)
		&& (obj1Dir != TWOD_MOVE_DIRECTION_E) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_SE) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_NE)
		){
		position = TWOD_POSITION_RIGHT;
	}
	// position bot left
	else if((obj1X1 < obj2X1) && (obj1Y3 > obj2Y3)
		&& (obj1Dir != TWOD_MOVE_DIRECTION_W) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_SW) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_S)
		){
		position = TWOD_POSITION_BOTLEFT;
	}
	// position bot 
	else if((obj1Y3 > obj2Y3) && (obj1X3 >= obj2X3) && (obj1X4 <= obj2X4)
		&& (obj1Dir != TWOD_MOVE_DIRECTION_S) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_SW) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_SE)
		){
		position = TWOD_POSITION_BOT;
	}
	// position bot right
	else if((obj1X4 > obj2X4) && (obj1Y4 > obj2Y4)
		&& (obj1Dir != TWOD_MOVE_DIRECTION_E) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_SE) 
		&& (obj1Dir != TWOD_MOVE_DIRECTION_S)
		){
		position = TWOD_POSITION_BOTRIGHT;
	}
	// position inside
	else if((obj1X1>=obj2X1) && (obj1Y1>=obj2Y1) && (obj1X4<=obj2X4) && (obj1Y4<=obj2Y4)){
		position = TWOD_POSITION_INSIDE;
	}
	// passed through left
	else if((oldObj1X2 <= obj2X1) && (obj1X1 >= obj2X1)){
		position = TWOD_POSITION_LEFT;
	}
	// passed through right
	else if((obj1X2 <= obj2X2) && (oldObj1X1 >= obj2X2)){
		position = TWOD_POSITION_RIGHT;
	}
	// passed through top
	else if((oldObj1Y2 <= obj2Y1) && (obj1Y1 >= obj2Y1)){
		position = TWOD_POSITION_TOP;
	}
	// passed through bottom
	else if((obj1Y2 <= obj2Y2) && (oldObj1Y1 >= obj2Y2)){
			position = TWOD_POSITION_BOT;
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

void twoDEngine::autoFixCollision(twoDObject *obj1, twoDObject *obj2, int position){
	int moveX, moveY;
	int obj1X, obj1Y, obj1W, obj1H;
	int obj1Dir, obj1OldX, obj1OldY;
	bool onTop, onLeft, onRight, onBottom;

	obj1X = obj1->getX();
	obj1Y = obj1->getY();
	obj1W = obj1->getWidth();
	obj1H = obj1->getHeight();
	obj1OldX = obj1->getOldX();
	obj1OldY = obj1->getOldY();

	obj1Dir = obj1->getMovement()->getDirection();
	onTop = onLeft = onRight = onBottom = false;
	obj1->setState(TWOD_STATE_COLLIDING);
	moveX = 0;
	moveY = 0;

	switch(position){
		case TWOD_POSITION_TOPLEFT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_E:
					onRight = true;
					break;
				case TWOD_MOVE_DIRECTION_S:
					onBottom = true;
					break;
				case TWOD_MOVE_DIRECTION_SE:
					if((obj1OldX + obj1W - 1) > obj2->getX())
						onBottom = true;
					else
						onRight = true;
					break;
				case TWOD_MOVE_DIRECTION_NE:
					onRight = true;
					break;
				case TWOD_MOVE_DIRECTION_SW:
					onBottom = true;
					break;
			}
			break;
		case TWOD_POSITION_TOP:
			onBottom = true;
			break;
		case TWOD_POSITION_TOPRIGHT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_W:
					onLeft = true;
					break;
				case TWOD_MOVE_DIRECTION_S:
					onBottom = true;
					break;
				case TWOD_MOVE_DIRECTION_SW:
					if(obj1OldX < (obj2->getX() + obj2->getWidth() - 1))
						onBottom = true;
					else
						onLeft = true;
					break;
				case TWOD_MOVE_DIRECTION_NW:
					onLeft = true;
					break;
				case TWOD_MOVE_DIRECTION_SE:
					onBottom = true;
					break;
			}
			break;
		case TWOD_POSITION_LEFT:
			onRight = true;
			break;
		case TWOD_POSITION_RIGHT:
			onLeft = true;
			break;
		case TWOD_POSITION_BOTLEFT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_E:
					onRight = true;
					break;
				case TWOD_MOVE_DIRECTION_N:
					onTop = true;
					break;
				case TWOD_MOVE_DIRECTION_NE:
					if((obj1OldX + obj1W - 1) > obj2->getX())
						onTop = true;
					else
						onRight = true;
					break;
				case TWOD_MOVE_DIRECTION_SE:
					onRight = true;
					break;
				case TWOD_MOVE_DIRECTION_NW:
					onTop = true;
					break;
			}
			break;
		case TWOD_POSITION_BOT:
			onTop = true;
			break;
		case TWOD_POSITION_BOTRIGHT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_W:
					onLeft = true;
					break;
				case TWOD_MOVE_DIRECTION_N:
					onTop = true;
					break;
				case TWOD_MOVE_DIRECTION_NW:
					if(obj1OldX < (obj2->getX() + obj2->getWidth() - 1))
						onTop = true;
					else
						onLeft = true;
					break;
				case TWOD_MOVE_DIRECTION_SW:
					onLeft = true;
					break;
				case TWOD_MOVE_DIRECTION_NE:
					onTop = true;
					break;
			}
			break;
	}

	if(onRight)
		moveX = obj2->getX() - (obj1X + obj1W);
	else if(onLeft)
		moveX = (obj2->getX() + obj2->getWidth()) - obj1X;

	if(onTop)
		moveY = (obj2->getY() + obj2->getHeight()) - obj1Y;
	else if(onBottom){
		moveY = obj2->getY() - (obj1Y + obj1H);
		obj1->getMovement()->stopFalling();
	}

	obj1->move(moveX,moveY);
	obj1->setOldPosition(obj1OldX, obj1OldY);
}

void twoDEngine::autoRedirectCollision(twoDObject *obj1, twoDObject *obj2, int position){
	int obj1Dir;
	twoDMovement *obj1Mv;

	obj1Mv = obj1->getMovement();
	obj1Dir = obj1Mv->getDirection();
	obj1->setState(TWOD_STATE_COLLIDING);

	switch(position){
		case TWOD_POSITION_TOP:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_S:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_N);
					break;
				case TWOD_MOVE_DIRECTION_SW:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NW);
					break;
				case TWOD_MOVE_DIRECTION_SE:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NE);
					break;
			}
			break;
		case TWOD_POSITION_RIGHT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_W:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_E);
					break;
				case TWOD_MOVE_DIRECTION_NW:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NE);
					break;
				case TWOD_MOVE_DIRECTION_SW:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SE);
					break;
			}
			break;
		case TWOD_POSITION_BOT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_N:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_S);
					break;
				case TWOD_MOVE_DIRECTION_NW:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SW);
					break;
				case TWOD_MOVE_DIRECTION_NE:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SE);
					break;
			}
			break;
		case TWOD_POSITION_LEFT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_E:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_W);
					break;
				case TWOD_MOVE_DIRECTION_NE:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NW);
					break;
				case TWOD_MOVE_DIRECTION_SE:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SW);
					break;
			}
			break;
		case TWOD_POSITION_TOPRIGHT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_W:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_E);
					break;
				case TWOD_MOVE_DIRECTION_NW:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NE);
					break;
				case TWOD_MOVE_DIRECTION_SW:
					if(obj1->getOldX() < (obj2->getX() + obj2->getWidth() - 1))
						obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NW);
					else
						obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SE);
					break;
				case TWOD_MOVE_DIRECTION_S:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_N);
					break;
				case TWOD_MOVE_DIRECTION_SE:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NE);
					break;
			}
			break;
		case TWOD_POSITION_TOPLEFT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_E:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_W);
					break;
				case TWOD_MOVE_DIRECTION_NE:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NW);
					break;
				case TWOD_MOVE_DIRECTION_SE:
					if((obj1->getOldX() + obj1->getWidth() - 1) > obj2->getX())
						obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NE);
					else
						obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SW);
					break;
				case TWOD_MOVE_DIRECTION_S:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_N);
					break;
				case TWOD_MOVE_DIRECTION_SW:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NW);
					break;
			}
			break;
		case TWOD_POSITION_BOTLEFT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_E:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_W);
					break;
				case TWOD_MOVE_DIRECTION_SE:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SW);
					break;
				case TWOD_MOVE_DIRECTION_NE:
					if((obj1->getOldX() + obj1->getWidth() - 1) > obj2->getX())
						obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SE);
					else
						obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NW);
					break;
				case TWOD_MOVE_DIRECTION_N:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_S);
					break;
				case TWOD_MOVE_DIRECTION_NW:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SW);
					break;
			}
			break;
		case TWOD_POSITION_BOTRIGHT:
			switch(obj1Dir){
				case TWOD_MOVE_DIRECTION_W:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_E);
					break;
				case TWOD_MOVE_DIRECTION_SW:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SE);
					break;
				case TWOD_MOVE_DIRECTION_NW:
					if(obj1->getOldX() < (obj2->getX() + obj2->getWidth() - 1))
						obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SW);
					else
						obj1Mv->setDirection(TWOD_MOVE_DIRECTION_NE);
					break;
				case TWOD_MOVE_DIRECTION_N:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_S);
					break;
				case TWOD_MOVE_DIRECTION_NE:
					obj1Mv->setDirection(TWOD_MOVE_DIRECTION_SE);
					break;
			}
			break;
	}
}

twoDObject * twoDEngine::removeObject(twoDObject *obj){
	int layer, i, k;

	layer = obj->getLayer();
	k = -1;

	for(i=0; i<TWOD_OBJ_PER_LAYER; i++){
		if(this->layer[layer][i] == NULL)
			break;
		if(this->layer[layer][i] == obj)
			k = i;
	}
	i--;

	if(k != -1){
		this->layer[layer][k] = this->layer[layer][i];
		this->layer[layer][i] = NULL;
		return obj;
	}
	
	return NULL;
}

