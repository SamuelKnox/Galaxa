#ifndef _ET_H
#define _ET_H

#include "Sprite.h"
#include "gamedefs.h"

class Player : public Sprite
{
public:

    // Factory function
    static Player* CreatePlayer(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int32_t gameObjectType);
	~Player();

	void updateET(uint32_t milliseconds);
	void playerHit();
	void DrawLivesLeft();

    void setFireSfxId(uint32_t fireSFXId) { mFireSFXId = fireSFXId; };
	enum WEAPON_TYPES 
	{
		NORMAL,
		QUICK,
		SPREAD,
		HOMING
	};
	int32_t currentWeapon = NORMAL;

private:
    Player(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int32_t gameObjectType);



	bool8_t mIsMoving;
	bool8_t mCanMove;
	bool8_t mCanShoot;

	int32_t mNumLives;

	float_t mMoveForce;
    uint32_t mShotTimer;

    uint32_t mFireSFXId;
    uint32_t mHitSFXId;
	Sprite* mLives[PLAYER_LIVES] = { nullptr };

	void CheckForUserInput();
	void CheckBoundaries();
	void Shoot();
};

#endif