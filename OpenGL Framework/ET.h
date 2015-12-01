#ifndef _ET_H
#define _ET_H

#include "Sprite.h"
#include "gamedefs.h"

class ET : public Sprite
{
public:

	ET(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int32_t gameObjectType);
	~ET();

	void updateET(DWORD milliseconds);
	void playerHit();
	void DrawLivesLeft();

private:
	bool8_t mIsMoving;
	bool8_t mCanMove;
	bool8_t mCanShoot;

	int32_t mNumLives;

	float_t mMoveForce;
	DWORD mShotTimer;

	Sprite* mLives[PLAYER_LIVES] = { nullptr };

	void CheckForUserInput();
	void CheckBoundaries();
};

#endif