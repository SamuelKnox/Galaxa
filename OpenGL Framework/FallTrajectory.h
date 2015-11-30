#ifndef _FALL_TRAJECTORY_H_
#define _FALL_TRAJECTORY_H_

#include "baseTypes.h"
#include "gamedefs.h"
#include "Trajectory.h"

class FallTrajectory :
    public Trajectory
{
public:
    FallTrajectory();
    ~FallTrajectory();

    void update(DWORD milliseconds);

private:
    static const float_t FALLSPEED;
};

#endif
