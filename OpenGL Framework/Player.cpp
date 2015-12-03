#define ET_CPP

#include <iostream>
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include "jsy/jsy.h"
#include "collInfo.h"
#include "object.h"
#include "Sprite.h"
#include "Player.h"

#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "game.h"


Player* Player::CreatePlayer(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int32_t gameObjectType) {
	Player* player = new Player(initPosX, initPosY, initVelX, initVelY, gameObjectType);

	static uint32_t firSfxId = SoundManager::GetInstance()->LoadSound(PLAYER_SFX_FIRE);
	static uint32_t hitSfxId = SoundManager::GetInstance()->LoadSound(PLAYER_SFX_HIT);
	player->mFireSFXId = firSfxId;
	player->mHitSFXId = hitSfxId;
	return player;
}

Player::Player(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int32_t gameObjectType)
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
	mNumLives = PLAYER_LIVES;

	for (int32_t i = 1; i <= mNumLives; i++)
	{
		// Get position for lives based on screen size and half player's actual size to
		//	place them in the bottom-left corner;
		float_t xPos = (-BG_WIDTH / 2.0f) + i * (mWidth / 2.0f);
		float_t yPos = (BG_HEIGHT / 2.0f) - (mHeight / 2.0f);
		mLives[i - 1] = new Sprite(xPos, yPos, mWidth / 2.0f, mHeight / 2.0f, SpriteManager::PLAYER);
	}
}

Player::~Player()
{};

void Player::updateET(uint32_t milliseconds)
{
	// Check if dead
	if (mNumLives < 0)
	{
		SpriteManager::GetInstance()->endGame();
		return;
	}

	// Update shot timer
	if (!mCanShoot)
	{
		mShotTimer += milliseconds;
		switch (currentWeapon) {
		case NormalWeapon:
			if (mShotTimer >= NORMAL_SHOT_RATE)
			{
				mCanShoot = true;
			}
			break;
		case QuickWeapon:
			if (mShotTimer >= QUICK_SHOT_RATE)
			{
				mCanShoot = true;
			}
			break;
		case SpreadWeapon:
			if (mShotTimer >= SPREAD_SHOT_RATE)
			{
				mCanShoot = true;
			}
			break;
		case HomingWeapon:
			if (mShotTimer >= HOMING_SHOT_RATE)
			{
				mCanShoot = true;
			}
			break;
		default:
			mCanShoot = false;
			break;
		}
	}

	// Check for movement input if able to move
	if (mCanMove)
	{
		CheckForUserInput();
	}

	CheckBoundaries();
}

void Player::playerHit()
{
	mNumLives--;
	SoundManager::GetInstance()->PlaySoundResource(mHitSFXId);
	if (mNumLives >= 0)
	{
		delete mLives[mNumLives];
		mLives[mNumLives] = nullptr;
	}

}

void Player::CheckForUserInput()
{

	float_t keyLeft, keyRight, keyUp, keyDown, keyShoot;

	JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_LEFT, &keyLeft);
	JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_RIGHT, &keyRight);
	JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_UP, &keyUp);
	JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_DOWN, &keyDown);
	JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_A, &keyShoot);

	// Check vertical movement
	if ((keyUp > 0.0f))
	{
		mVelocity.y = MOVE_FORCE;
	}
	else if ((keyDown > 0.0f))
	{
		mVelocity.y = -MOVE_FORCE;
	}
	else
	{
		mVelocity.y = 0.0f;
	}

	// Check horizontal movement
	if ((keyLeft > 0.0f))
	{
		mVelocity.x = -MOVE_FORCE;
		mIsFacingLeft = true;
	}
	else if ((keyRight > 0.0f))
	{
		mVelocity.x = MOVE_FORCE;
		mIsFacingLeft = false;
	}
	else
	{
		mVelocity.x = 0.0f;
	}

	// Check for firing missles
	if (mCanShoot && (keyShoot > 0.0f)) {
		mCanShoot = false;
		mShotTimer = 0;
		Shoot();
		if (mFireSFXId != 0) {
			SoundManager::GetInstance()->PlaySoundResource(mFireSFXId);
		}
	}
}

void Player::Shoot() {
	float_t spreadAngle;
	Bullet* homingBullet;
	switch (currentWeapon) {
	case NormalWeapon:
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, 0.0f, SHOT_FORCE, SpriteManager::PLAYER);
		break;
	case QuickWeapon:
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, 0.0f, QUICK_SHOT_FORCE, SpriteManager::PLAYER);
		break;
	case SpreadWeapon:
		spreadAngle = atanf(SPREAD_SHOT_ANGLE / SPREAD_SHOT_FORCE);
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, -spreadAngle, SPREAD_SHOT_FORCE, SpriteManager::PLAYER);
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, 0.0f, SPREAD_SHOT_FORCE, SpriteManager::PLAYER);
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, spreadAngle, SPREAD_SHOT_FORCE, SpriteManager::PLAYER);
		break;
	case HomingWeapon:
		homingBullet = SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, 0.0f, HOMING_FORCE, SpriteManager::PLAYER);
		homingBullet->homingMissile = true;
		break;
	default:
		break;

	}
}

void Player::CheckBoundaries()
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

void Player::DrawLivesLeft()
{
	for (int32_t i = 0; i < mNumLives; i++)
	{
		mLives[i]->render();
	}
}
