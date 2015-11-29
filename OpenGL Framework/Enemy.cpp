#include "gamedefs.h"
#include "SOIL.h"
#include "Enemy.h"

Enemy::Enemy() {

    mWidth = ENEMY_WIDTH;
    mHeight = ENEMY_HEIGHT;

    mEnabled = true;

    currentSprite = 0;
    numSprites = PLAYER_NUM_SPRITES;
    mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

    // TODO: Move this to interface layer to make platform-independent
    mSpriteID = SOIL_load_OGL_texture(ENEMY_SPRITE_GREEN, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

Enemy::Enemy(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY)
{
    mPosition.x = initPosX;
    mPosition.y = initPosY;
    mVelocity.x = initVelX;
    mVelocity.y = initVelY;

    mWidth = ENEMY_WIDTH;
    mHeight = ENEMY_HEIGHT;

    mEnabled = true;

    currentSprite = 0;
    numSprites = PLAYER_NUM_SPRITES;
    mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

    // TODO: Move this to interface layer to make platform-independent
    mSpriteID = SOIL_load_OGL_texture(ENEMY_SPRITE_GREEN, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
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
