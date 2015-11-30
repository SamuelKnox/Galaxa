#ifndef _OBJECT_H
#define _OBJECT_H

#include "baseTypes.h"
#include "collInfo.h"

class ObjectC
{
public:
    ObjectC(float initPosX, float initPosY, float initVelX, float initVelY);
    ObjectC();
    virtual ~ObjectC();
    virtual void setPosition(Coord2D *posToSet) {mPosition.x = posToSet->x;mPosition.y = posToSet->y;};
    virtual void setPosition(float x, float y) { mPosition.x = x; mPosition.y = y; };
    Coord2D *getPosition() {return &mPosition;};
    void setVelocity(Coord2D *velToSet) {mVelocity.x = velToSet->x;mVelocity.y = velToSet->y;};
    void setVelocity(float x, float y) {mVelocity.x = x;mVelocity.y = y;};
    Coord2D *getVelocity() {return &mVelocity;};
    void setCollInfo(CollInfoC *collInfoToSet) {mCollInfo = *collInfoToSet;};
    CollInfoC *getCollInfo() {return &mCollInfo;};
	int32_t getID() {return mID;};
	void setID(int32_t id) {mID = id;};
	virtual void render()=0;
protected:
    Coord2D mPosition;
    Coord2D mVelocity;
    CollInfoC mCollInfo;
	int32_t mID;
};

#endif