#ifndef _BULLET_MANAGER_H
#define _BULLET_MANAGER_H


#include <iostream>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "soil.h"

#include "Object.h"
#include "Sprite.h"
#include "Bullet.h"
#include "SpriteManager.h"
#include "gamedefs.h"


Bullet::Bullet(float_t x, float_t y, float_t xVel, float_t yVel, int32_t gameObjectType)
{
	// Object
	mPosition.x = x;
	mPosition.y = y;
	mVelocity.x = xVel;
	mVelocity.y = yVel;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// Sprite
	mWidth = MISSILE_WIDTH;
	mHeight = MISSILE_HEIGHT;
	numSprites = MISSILE_NUM_SPRITES;
	currentSprite = 0;

	mType = gameObjectType;

	mEnabled = true;
	mIsFacingLeft = false;
}


Bullet::~Bullet()
{
}


#endif
