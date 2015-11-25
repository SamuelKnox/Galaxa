#pragma once
#include "Sprite.h"
#include "Physics.h"

class Collidable :
	public Sprite
{
public:
	Collidable(char* collidableID, float x, float y, char* image);
	~Collidable();
	bool IsColliding(Collidable other);
};