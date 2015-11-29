#include "Trajectory.h"


Trajectory::Trajectory()
{
}

Trajectory::Trajectory(const Coord2D & position)
{
    mPosition.x = position.x;
    mPosition.y = position.y;
}


Trajectory::~Trajectory()
{
}

void Trajectory::GetPosition(Coord2D & position) const {

}

void Trajectory::SetPosition(const Coord2D & position) {
    mPosition.x = position.x;
    mPosition.y = position.y;
}

