#ifndef _OBJINCLUDE_H
#define _OBJINCLUDE_H

#include "Object.h"
//#include "jsy/jsy.h"
//#include "collInfo.h"

ObjectC::ObjectC(float initPosX, float initPosY, float initVelX, float initVelY)
{
    mPosition.x = initPosX;
    mPosition.y = initPosY;
    mVelocity.x = initVelX;
    mVelocity.y = initVelY;
};
ObjectC::ObjectC()
{
    mPosition.x = 0.0f;
    mPosition.y = 0.0f;
    mVelocity.x = 0.0f;
    mVelocity.y = 0.0f;
};
ObjectC::~ObjectC()
{
};

#endif