#include "Physics.h"



Physics::Physics()
{
}


Physics::~Physics()
{
}

void Physics::RegisterCollidable(Collidable* collidable) {
	collidables->Add(collidable);
}

Collidable* Physics::SendMoveEvent(Movable* movable) {
	for each (Collidable* collidable in collidables)
	{
		if (collidable->IsColliding(*movable)) {
			return collidable;
		}
	}
}