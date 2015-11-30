#define EXPLOSION_CPP

#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include "baseTypes.h"
#include "collInfo.h"
#include "object.h"
#include "Sprite.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "SpriteManager.h"

#include "Explosion.h"

Explosion::Explosion(float_t initPosX, float_t initPosY, int32_t explosionType)
{
	// Object
	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mVelocity.x = 0.0f;
	mVelocity.y = 0.0f;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// Sprite
	if (explosionType == SpriteManager::EXPLOSION_PLAYER)
	{
		mWidth = EXPLOSION_PLAYER_WIDTH;
		mHeight = EXPLOSION_PLAYER_HEIGHT;
		numSprites = EXPLOSION_NUM_SPRITES;
	}
	else if (explosionType == SpriteManager::EXPLOSION_ENEMY)
	{
		mWidth = EXPLOSION_ENEMY_WIDTH;
		mHeight = EXPLOSION_ENEMY_HEIGHT;
		numSprites = EXPLOSION_NUM_SPRITES;
	}
	
	currentSprite = START; // No animations

	mType = explosionType;

	mEnabled = true;
	mIsFacingLeft = false;
}


Explosion::~Explosion()
{}

bool8_t Explosion::CycleExplosionAnimation()
{
	if (currentSprite < END)
	{
		currentSprite++;
		return false;
	}
	else
	{
		return true;
	}
}
