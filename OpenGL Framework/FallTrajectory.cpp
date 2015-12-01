#include "FallTrajectory.h"
#include <iostream>

const float FallTrajectory::FALLSPEED = FALL_TRAJECTORY_SPEED;

FallTrajectory::FallTrajectory()
{
}


FallTrajectory::~FallTrajectory()
{
}

void FallTrajectory::update(DWORD milliseconds) {
    mPosition.y -= FallTrajectory::FALLSPEED * milliseconds / 1000;
    mPosition.x = 20 * sin(mPosition.y / 10) + mOriginalPosition.x;
}
