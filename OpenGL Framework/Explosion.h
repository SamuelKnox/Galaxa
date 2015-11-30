#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include "Sprite.h"

class Explosion : public Sprite
{

public:
	enum EXPLOSION_STATES
	{
		START,
		MIDDLE_1,
		MIDDLE_2,
		END
	};

	Explosion(float_t initPosX, float_t initPosY, int32_t explosionType);
	~Explosion();

	bool8_t CycleExplosionAnimation();
};

#endif