#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <windows.h>

#include "jsy/types.h"
#include "Sprite.h"
#include "Trajectory.h"

class Enemy : public Sprite
{
public:
    Enemy();
    ~Enemy();

    void update(DWORD milliseconds);
    void setSpriteType(int32_t type);
    void setPosition(float x, float y);
	void setTrajectory(Trajectory* newTrajectory);
    void setKillSfxId(uint32_t killSFXId) { mKillSFXId = killSFXId; };
    void reset();
    void killed();

private:
    Trajectory* mTrajectory;
    DWORD lastShootDuration = 0;

    uint32_t mKillSFXId;
};


#endif
