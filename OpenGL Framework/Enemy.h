#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <windows.h>

#include "baseTypes.h"
#include "Sprite.h"
#include "Trajectory.h"

class Enemy : public Sprite
{
public:
    Enemy(int32_t enemyType);
    ~Enemy();

    void SetTrajectory(Trajectory * trajectory) { mTrajectory = trajectory; };
    void update(DWORD milliseconds);

private:
    Trajectory* mTrajectory;

};


#endif
