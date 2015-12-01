#include <math.h>
#include "gamedefs.h"
#include "SOIL.h"
#include "Enemy.h"
#include "FallTrajectory.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "Player.h"

Enemy::Enemy()
{
	// Object
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;
	mVelocity.x = 0.0f;
	mVelocity.y = 0.0f;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// Sprite
    mWidth = ENEMY_WIDTH;
    mHeight = ENEMY_HEIGHT;
	numSprites = ENEMY_NUM_SPRITES;
	currentSprite = 0;	// No animations

    mEnabled = true;
	mIsFacingLeft = false;

    mTrajectory = new FallTrajectory();

}

Enemy::~Enemy()
{
    SoundManager::GetInstance()->PlaySoundResource(mKillSFXId);
    if (mTrajectory != nullptr) {
        delete mTrajectory;
    }
}

void Enemy::update(DWORD milliseconds)
{
    // Update the enemy position according the Trajectory
    if (mTrajectory != nullptr) {
        mTrajectory->update(milliseconds);
        mTrajectory->GetPosition(mPosition);
    }

    // Check for firing missles
    lastShootDuration += milliseconds;
    if (lastShootDuration >= ENEMY_SHOOT_TIME_MILLISEC) {
        lastShootDuration = 0;
        Player * player = SpriteManager::GetInstance()->getET();
        float_t velX = (player->getPosition()->x - (mPosition.x));
        float_t velY = (player->getPosition()->y - (mPosition.y));
        float_t length = (float_t) sqrt(velY * velY + velX * velX);
        velY *= SHOT_FORCE / length;
        velX *= SHOT_FORCE / length;
        SpriteManager::GetInstance()->CreateBullet(mPosition.x, mPosition.y, velX, velY, SpriteManager::ENEMY_GREEN);
    }
}

void Enemy::setSpriteType(int32_t type) {
    mType = type;
    currentSprite = 0;
}

void Enemy::reset() {
    mTrajectory->reset();
}

void Enemy::setPosition(float x, float y) {
    mPosition.x = x;
    mPosition.y = y;
    mTrajectory->SetPosition(mPosition);
}
