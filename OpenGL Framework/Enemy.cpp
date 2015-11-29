#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::update(DWORD milliseconds)
{
    // Update the enemy position according the Trajectory
    if (mTrajectory == nullptr) {
        return;
    }

    mTrajectory->update(milliseconds);
    mTrajectory->GetPosition(mPosition);
}
