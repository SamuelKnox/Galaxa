#include "EntityFactory.h"



EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

Entity* EntityFactory::CreateEntity() {
	Entity* entity = new Entity();
	delete entity;
	return nullptr;
}

Sprite* EntityFactory::CreateSprite() {
	Sprite* sprite = new Sprite();
	delete sprite;
	return nullptr;
}

Collidable* EntityFactory::CreateCollidable() {
	Collidable* collidable = new Collidable();
	delete collidable;
	return nullptr;
}

Movable* EntityFactory::CreateMovable() {
	Movable* movable = new Movable();
	delete movable;
	return nullptr;
}