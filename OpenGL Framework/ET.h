#ifndef _ET_H
#define _ET_H

class ET : public Sprite
{
public:
	enum ET_STATES
	{
		ET_IDLE,
		ET_RUN1,
		ET_RUN2,
		ET_NECK1,
		ET_NECK2,
		ET_NECK3,
		ET_NECK4
	};

	ET(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY);
	~ET();

	void update(DWORD milliseconds);

private:
	bool8_t mIsMoving;
	bool8_t mCanMove;

	float_t mMoveForce;

	void CheckForUserInput();
	void CheckBoundaries();
};

#endif