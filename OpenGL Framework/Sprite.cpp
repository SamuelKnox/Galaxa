#include <iostream>
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include "jsy/jsy.h"
#include "collInfo.h"
#include "object.h"
//#include "inputmapper.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"
#include "game.h"

#include "jsy/jsy.h"

Sprite::Sprite()
{

}

Sprite::Sprite(float_t initPosX, float_t initPosY, float_t width, float_t height, int32_t gameObjectType)
{
	// Object
	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mVelocity.x = 0.0f;
	mVelocity.y = 0.0f;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// Sprite
	mWidth = width;
	mHeight = height;
	numSprites = 1;
	currentSprite = 0; // No animations

	mType = gameObjectType;

	mEnabled = true;
	mIsFacingLeft = false;
}

Sprite::~Sprite()
{}

void Sprite::update(uint32_t milliseconds) {
	if (mEnabled)
	{
		mPosition.x += mVelocity.x * milliseconds / 10;
		mPosition.y += mVelocity.y * milliseconds / 10;
	}	
}

void Sprite::render()
{
    if (!mEnabled)
        return;

	float_t xPosLeft = mPosition.x - mWidth / 2;
	float_t xPosRight = mPosition.x + mWidth / 2;
	float_t yPosTop = mPosition.y - mHeight / 2;
	float_t yPosBot = mPosition.y + mHeight / 2;

	float_t xTextureCoord = (float_t)currentSprite * (1.0f / numSprites);
	uint32_t spriteID = SpriteManager::GetInstance()->getSpriteTextureMap(mType);
    JsyGDrawSprite(CGame::GetInstance()->GetJsyHandle(), spriteID, mIsFacingLeft, xPosLeft, xPosRight, yPosTop, yPosBot, xTextureCoord, numSprites);
}

void Sprite::setSpriteType(int32_t type) {
    mType = type;
    currentSprite = 0;
}