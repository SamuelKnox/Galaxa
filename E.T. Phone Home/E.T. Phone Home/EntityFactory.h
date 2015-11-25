#include "Movable.h"

#pragma once
class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	static Entity* CreateEntity();
	static Sprite* CreateSprite();
	static Collidable* CreateCollidable();
	static Movable* CreateMovable();
};