#ifndef _COLLIDABLE_H_
#define _COLLIDABLE_H_

#include "Sprite.h"

class Collidable : public Sprite
{

public:
	Collidable();
	~Collidable();

	bool8_t IsColliding(Collidable other);
};

#endif