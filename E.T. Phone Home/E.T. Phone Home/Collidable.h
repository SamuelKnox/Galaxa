#pragma once
#include "Sprite.h"
class Collidable :
	public Sprite
{
public:
	Collidable();
	~Collidable();
	bool IsColliding(Collidable other);
};