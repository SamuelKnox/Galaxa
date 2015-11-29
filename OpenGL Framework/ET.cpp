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


ET::ET(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY)
{

	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mVelocity.x = initVelX;
	mVelocity.y = initVelY;

	mWidth = PLAYER_WIDTH;
	mHeight = PLAYER_HEIGHT;

	mEnabled = true;
	mIsMoving = false;
	mCanMove = true;
	mIsFacingLeft = false;

	currentSprite = 0;
	numSprites = PLAYER_NUM_SPRITES;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// TODO: Move this to interface layer to make platform-independent
	mSpriteID = SOIL_load_OGL_texture(PLAYER_SPRITE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	
}

ET::~ET()
{};

void ET::updateET(DWORD milliseconds)
{
	// Check for movement input and update position
	CheckForUserInput();
	//mPosition.x += mVelocity.x*milliseconds / 10;
	//mPosition.y += mVelocity.y*milliseconds / 10;

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

	if ((keyUp & 0x8000))
	{
		mVelocity.y = 1.0f;
	}
	else if ((keyDown & 0x8000))
	{
		mVelocity.y = -1.0f;
	}
	else
	{
		mVelocity.y = 0.0f;
	}

	if ((keyLeft & 0x8000))
	{
		mVelocity.x = -1.0f;
		mIsFacingLeft = true;
	}
	else if ((keyRight & 0x8000))
	{
		mVelocity.x = 1.0f;
		mIsFacingLeft = false;
	}
	else
	{
		mVelocity.x = 0.0f;
	}
	if (keyShoot & 0x8000) {
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, 0, 1.0f);
	}
}

void ET::CheckBoundaries()
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();

	float_t rightSide = field->getPosition()->x + ((float_t)field->getWidth() / 2.0f);
	float_t leftSide = field->getPosition()->x - ((float_t)field->getWidth() / 2.0f);
	float_t topSide = field->getPosition()->y - ((float_t)field->getHeight() / 2.0f);
	float_t bottomSide = field->getPosition()->y + ((float_t)field->getHeight() / 2.0f);


	// TODO: These will become transitions to different levels on each side
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
