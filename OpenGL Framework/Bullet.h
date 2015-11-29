#pragma once
#include "Sprite.h"
class Bullet : public Sprite
{
public:
	Bullet(float_t x, float_t y, float_t xVel, float_t yVel);
	~Bullet();
};

