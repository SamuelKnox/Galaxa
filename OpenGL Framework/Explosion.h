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
		END,
		POINTS
	};

	Explosion(float_t initPosX, float_t initPosY, uint32_t explosionType, uint32_t pointType);
	~Explosion();

	bool8_t CycleExplosionAnimation(DWORD milliseconds);

private:

	bool8_t mIsFinished;
	uint32_t mPointType;
	DWORD mAnimationRate;
	DWORD mAnimationTimer;
};

#endif