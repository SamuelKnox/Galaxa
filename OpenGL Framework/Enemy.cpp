#include "gamedefs.h"
#include "SOIL.h"
#include "Enemy.h"

Enemy::Enemy(int32_t enemyType) 
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

	mType = enemyType;

	// Enemy

}

Enemy::~Enemy()
{
}

void Enemy::update(DWORD milliseconds)
{
    // Update the enemy position according the Trajectory
    if (mTrajectory != nullptr) {
        mTrajectory->update(milliseconds);
        mTrajectory->GetPosition(mPosition);
    }
    else
    {

    }
}
