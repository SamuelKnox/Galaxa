#define ET_CPP

#include <iostream>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "soil.h"

#include "baseTypes.h"
#include "ShapeDraw.h"
#include "collInfo.h"
#include "object.h"
#include "Sprite.h"
#include "ET.h"

#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"
#include "SpriteManager.h"
#include "SoundManager.h"


ET::ET(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int32_t gameObjectType)
{
	// Object
	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mVelocity.x = initVelX;
	mVelocity.y = initVelY;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// Sprite
	mWidth = PLAYER_WIDTH;
	mHeight = PLAYER_HEIGHT;
	numSprites = PLAYER_NUM_SPRITES;
	currentSprite = 0; // No animations

	mType = gameObjectType;

	mEnabled = true;
	mIsFacingLeft = false;

	// Player
	mIsMoving = false;
	mCanMove = true;
	mCanShoot = true;
	mShotTimer = 0;
}

ET::~ET()
{};

void ET::updateET(DWORD milliseconds)
{
	// Update shot timer
	if (!mCanShoot)
	{
		mShotTimer += milliseconds;
		if (mShotTimer >= SHOT_RATE)
		{
			mCanShoot = true;
		}
	}

	// Check for movement input if able to move
	if (mCanMove)
	{
		CheckForUserInput();
	}

	CheckBoundaries();

	/*mIsMoving = (mVelocity.x != 0 || mVelocity.y != 0);
	if (mIsMoving)
	{
		currentSprite = (currentSprite + 1) % 3;
	}
	else
	{
		currentSprite = ET_IDLE;
	}*/
}

void ET::CheckForUserInput()
{
	SHORT keyLeft = GetKeyState(VK_LEFT);
	SHORT keyRight = GetKeyState(VK_RIGHT);
	SHORT keyUp = GetKeyState(VK_UP);
	SHORT keyDown = GetKeyState(VK_DOWN);
	SHORT keyShoot = GetKeyState(VK_SPACE);

	// Check vertical movement
	if ((keyUp & 0x8000))
	{
		mVelocity.y = MOVE_FORCE;
	}
	else if ((keyDown & 0x8000))
	{
		mVelocity.y = -MOVE_FORCE;
	}
	else
	{
		mVelocity.y = 0.0f;
	}

	// Check horizontal movement
	if ((keyLeft & 0x8000))
	{
		mVelocity.x = -MOVE_FORCE;
		mIsFacingLeft = true;
	}
	else if ((keyRight & 0x8000))
	{
		mVelocity.x = MOVE_FORCE;
		mIsFacingLeft = false;
	}
	else
	{
		mVelocity.x = 0.0f;
	}

	// Check for firing missles
	if (mCanShoot && (keyShoot & 0x8000)) {
		mCanShoot = false;
		mShotTimer = 0;
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, 0.0f, SHOT_FORCE, SpriteManager::PLAYER);
        if (mFireSFXId != 0) {
            SoundManager::GetInstance()->PlaySoundResource(mFireSFXId);
        }
	}
}

void ET::CheckBoundaries()
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();

	float_t rightSide = field->getPosition()->x + ((float_t)field->getWidth() / 2.0f);
	float_t leftSide = field->getPosition()->x - ((float_t)field->getWidth() / 2.0f);
	float_t topSide = field->getPosition()->y - ((float_t)field->getHeight() / 2.0f);
	float_t bottomSide = field->getPosition()->y + ((float_t)field->getHeight() / 2.0f);

	if (mPosition.x - mWidth / 2 <= leftSide)
	{
		mPosition.x = leftSide + mWidth / 2;
	}
	if (mPosition.x + mWidth / 2 >= rightSide)
	{
		mPosition.x = rightSide - mWidth / 2;
	}
	if (mPosition.y + mHeight / 2 >= bottomSide)
	{
		mPosition.y = bottomSide - mHeight / 2;
	}
	if (mPosition.y - mHeight / 2 <= topSide)
	{
		mPosition.y = topSide + mHeight / 2;
	}
}
