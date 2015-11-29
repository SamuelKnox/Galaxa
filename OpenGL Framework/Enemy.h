#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <windows.h>

#include "baseTypes.h"
#include "Sprite.h"
#include "Trajectory.h"

class Enemy : public Sprite
{
public:
    Enemy();
    ~Enemy();

    void SetTrajectory(Trajectory * trajectory) { mTrajectory = trajectory; };
    void update(DWORD milliseconds);
    void setSpriteType(int32_t type);

private:
    Trajectory* mTrajectory;

};


#endif
