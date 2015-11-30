#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#include "baseTypes.h"
#include <windows.h>

class Trajectory
{
public:
    Trajectory();
    Trajectory(const Coord2D & position);
    virtual ~Trajectory();

    virtual void update(DWORD milliseconds) = 0;
    void reset();
    void GetPosition(Coord2D & position) const;
    void SetPosition(const Coord2D & position);

protected:
    Coord2D mPosition;
    Coord2D mOriginalPosition;
    DWORD tickCount = 0;
};

#endif