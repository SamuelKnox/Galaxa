#include "Movable.h"

#pragma once
class Physics
{
public:
	Physics();
	~Physics();
	static void RegisterCollidable(Collidable* collidable);
	static Collidable* SendMoveEvent(Movable* movable);

private:
	static Collidable* collidables;
};

