#include <iostream>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library

#include "baseTypes.h"
#include "ShapeDraw.h"
#include "collInfo.h"
#include "object.h"
//#include "inputmapper.h"
#include "Sprite.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"

#include "soil.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{}

void Sprite::update(DWORD milliseconds) {
	mPosition.x += mVelocity.x*milliseconds / 10;
	mPosition.y += mVelocity.y*milliseconds / 10;
}

void Sprite::render()
{
	float_t xPosLeft = mPosition.x - mWidth / 2;
	float_t xPosRight = mPosition.x + mWidth / 2;
	float_t yPosTop = mPosition.y - mHeight / 2;
	float_t yPosBot = mPosition.y + mHeight / 2;

	float_t xTextureCoord = (float_t)currentSprite * (1.0f / numSprites);

	DrawSprite(mSpriteID, mIsFacingLeft, xPosLeft, xPosRight, yPosTop, yPosBot, xTextureCoord, (float_t)numSprites);
}

