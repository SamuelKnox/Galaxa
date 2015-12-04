#include "EntityFactory.h"

Entity* EntityFactory::CreateEntity(ENTITY_TYPES type) {
	switch (type)
	{
		case EntityFactory::ENTITY:
			return new Entity();
			break;
		case EntityFactory::SPRITE:
			return new Sprite();
			break;
		case EntityFactory::COLLIDABLE:
			return new Collidable();
			break;
		case EntityFactory::MOVABLE:
			return new Movable();
			break;
		default:
			return nullptr;
			break;
	}
}