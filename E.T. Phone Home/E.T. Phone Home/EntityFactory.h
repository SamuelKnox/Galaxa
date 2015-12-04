#ifndef _ENTITYFACTORY_H_
#define _ENTITYFACTORY_H_

#include "Entity.h"
#include "Sprite.h"
#include "Collidable.h"
#include "Movable.h"

class EntityFactory
{

public:
	enum ENTITY_TYPES
	{
		ENTITY,
		SPRITE,
		COLLIDABLE,
		MOVABLE
	};

	EntityFactory() { }
	~EntityFactory() { }

	Entity* CreateEntity(ENTITY_TYPES type);
};

#endif