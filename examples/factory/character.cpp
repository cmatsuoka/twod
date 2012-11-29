#include "character.h"

Character::Character(){
	this->leftSprite = new twoDSprite(CHARACTER_LEFT_SPRITE);
	this->rightSprite = new twoDSprite(CHARACTER_RIGHT_SPRITE);
	this->last = this->rightSprite;

	this->rightSprite->setSize(CHARACTER_SPRITE_WIDTH, CHARACTER_SPRITE_HEIGHT);
	this->leftSprite->setSize(CHARACTER_SPRITE_WIDTH, CHARACTER_SPRITE_HEIGHT);

	this->x = 0;
	this->y = 0;
	this->visible = true;
	this->collidable = true;
	this->autoFixCollision = true;
	this->layer = 0;
	this->state = TWOD_STATE_STANDING;
	this->width = this->rightSprite->getWidth();
	this->height = this->leftSprite->getHeight();

	this->movement = new twoDMovement(TWOD_MOVE_DIRECTION_NONE, CHARACTER_SPEED, 0, true);
}

void Character::update(twoDEngine *engine){
	this->moved = false;

	if(engine->keyPressed(KEY_LEFT))
		this->movement->setDirection(TWOD_MOVE_DIRECTION_W);
	else if(engine->keyPressed(KEY_RIGHT))
		this->movement->setDirection(TWOD_MOVE_DIRECTION_E);
	else
		this->movement->setDirection(TWOD_MOVE_DIRECTION_NONE);

	if(engine->keyPressed(KEY_A)){
		this->movement->setSpeed(CHARACTER_SPEED_RUN);
		this->rightSprite->setSwitchRate(CHARACTER_SPRITE_SPEED_RUN);
		this->leftSprite->setSwitchRate(CHARACTER_SPRITE_SPEED_RUN);
	}
	else{
		this->movement->setSpeed(CHARACTER_SPEED);
		this->rightSprite->setSwitchRate(CHARACTER_SPRITE_SPEED);
		this->leftSprite->setSwitchRate(CHARACTER_SPRITE_SPEED);
	}

	if(engine->keyPressed(KEY_SPACE))
		this->movement->jump();

	this->movement->apply((twoDObject*)this);
}

void Character::updatePosition(){
	this->leftSprite->setPosition(this->x, this->y);
	this->rightSprite->setPosition(this->x, this->y);
}

void Character::draw(){
	switch(this->movement->getDirection()){
		case TWOD_MOVE_DIRECTION_E:
			this->rightSprite->start();
			this->rightSprite->draw();
			this->last = this->rightSprite;
			break;
		case TWOD_MOVE_DIRECTION_SE:
			this->rightSprite->start();
			this->rightSprite->draw();
			this->last = this->rightSprite;
			break;
		case TWOD_MOVE_DIRECTION_W:
			this->leftSprite->start();
			this->leftSprite->draw();
			this->last = this->leftSprite;
			break;
		case TWOD_MOVE_DIRECTION_SW:
			this->leftSprite->start();
			this->leftSprite->draw();
			this->last = this->leftSprite;
			break;
		default:
			this->last->stop();
			this->last->draw();
			break;
	}
}

void Character::collision(twoDObject *obj, int position){
}

