#ifndef _OBJFACTORY_H_
#define _OBJFACTORY_H_

#include "../../twoD/factory.h"
#include "../../twoD/objects/border.h"
#include "character.h"
#include "wall.h"
#include "info.h"

class objFactory: public twoDFactory {

public:
	objFactory();
	twoDObject * createObject(map<string, void *>);
};

#endif

