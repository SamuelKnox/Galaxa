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
#include "gamedefs.h"


Bullet::Bullet()
{
	mPosition.x = 0;
	mPosition.y = 0;
	mVelocity.x = 0;
	mVelocity.y = 0;

	mWidth = BULLET_WIDTH;
	mHeight = BULLET_HEIGHT;

	mEnabled = true;
	mIsFacingLeft = false;

	numSprites = BULLET_NUM_SPRITES;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// TODO: Move this to interface layer to make platform-independent
	mSpriteID = SOIL_load_OGL_texture(BULLET_SPRITE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}


Bullet::~Bullet()
{
}


#endif
