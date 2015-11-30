#define SPRITE_MANAGER_CPP
#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>	// Header File For Variable Argument Routines
#include <math.h>	// Header File For Math Operations
#include <gl\gl.h>	// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "SOIL.h"

#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "Sprite.h"
#include "ET.h"
#include "Bullet.h"
#include "random.h"
#include "field.h"
#include "FieldManager.h"
#include "stateManager.h"
#include "SpriteManager.h"
#include "random.h"
#include "GameManager.h"


SpriteManager* SpriteManager::sInstance = NULL;


SpriteManager *SpriteManager::CreateInstance()
{
	assert(sInstance == NULL);
	sInstance = new SpriteManager();
	return sInstance;
}

SpriteManager::~SpriteManager() {
    for (int i = 0; i < ENEMY_MAX_ENEMIES; i++) {
        if (enemies[i] != nullptr) {
            delete enemies[i];
        }
    }
}

void SpriteManager::init()
{
	printf("Initing the SpriteManager.\n");

	spriteTextureMaps = (GLuint*)malloc(NUM_OBJECTS * sizeof(GLuint));
	spriteTextureMaps[PLAYER] = SOIL_load_OGL_texture(PLAYER_SPRITE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	spriteTextureMaps[ENEMY_GREEN] = SOIL_load_OGL_texture(ENEMY_SPRITE_GREEN, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	spriteTextureMaps[ENEMY_PURPLE] = SOIL_load_OGL_texture(ENEMY_SPRITE_PURPLE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	spriteTextureMaps[BULLET] = SOIL_load_OGL_texture(MISSILE_SPRITE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	player = new ET(0.0f, 0.0f, 0.0f, 0.0f, PLAYER);

	bullets = (Bullet**)malloc(MAX_NUM_MISSILES * sizeof(Bullet*));
	for (int i = 0; i < MAX_NUM_MISSILES; i++) {
		bullets[i] = nullptr;
	}
}

void SpriteManager::updateSprites(DWORD milliseconds)
{
	player->update(milliseconds);
	player->updateET(milliseconds);
	for (int i = 0; i < MAX_NUM_MISSILES; i++) {
		if (bullets[i] != nullptr) {
			bullets[i]->update(milliseconds);
		}
	}


    lastSpawnDuration += milliseconds;
    if (lastSpawnDuration >= ENEMY_RESPAWN_TIME_MILLISEC) {
        lastSpawnDuration = 0;
        spawnEnemy();
    }

	CheckBulletCollisions();
}

ET* SpriteManager::getET()
{
	return player;
}

void SpriteManager::renderSprites()
{
	player->render();


	for (int i = 0; i < MAX_NUM_MISSILES; i++) {
		if (bullets[i] != nullptr) {
			bullets[i]->render();
		}
	}


    for (int i = 0; i < ENEMY_MAX_ENEMIES; i++) {
        if (enemies[i] != nullptr) {
            enemies[i]->render();
        }
    }
}
GLuint SpriteManager::getSpriteTextureMap(int32_t objectType)
{
	return spriteTextureMaps[objectType];
}
void SpriteManager::shutdown()
{
	delete player;
	for (int i = 0; i < MAX_NUM_MISSILES; i++)
	{
		delete bullets[i];
	}

	free(spriteTextureMaps);
	free(bullets);
}

void SpriteManager::CreateBullet(float_t x, float_t y, float_t xVel, float_t yVel, int32_t ownerType) 
{
	for (int i = 0; i < MAX_NUM_MISSILES; i++) 
	{
		if (bullets[i] == nullptr) {
			bullets[i] = new Bullet(x, y, xVel, yVel, BULLET, ownerType);
			break;
		}
	}
}

void SpriteManager::CheckBulletCollisions()
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();
	float_t leftSide = field->getPosition()->x - ((float_t)field->getWidth() / 2.0f);
	float_t rightSide = field->getPosition()->x + ((float_t)field->getWidth() / 2.0f);
	float_t topSide = field->getPosition()->y - ((float_t)field->getHeight() / 2.0f);
	float_t bottomSide = field->getPosition()->y + ((float_t)field->getHeight() / 2.0f);

	for (int32_t i = 0; i < MAX_NUM_MISSILES; i++)
	{
		if (bullets[i] != nullptr)
		{
			Bullet *missile = bullets[i];
			float_t missileLeft = missile->getPosition()->x - missile->getWidth() / 2;
			float_t missileRight = missile->getPosition()->x + missile->getWidth() / 2;
			float_t missileUp = missile->getPosition()->y - missile->getHeight() / 2;
			float_t missileDown = missile->getPosition()->y + missile->getHeight() / 2;

			// Check if missile is out of bounds 
			if ((missileLeft <= leftSide) || (missileRight >= rightSide) ||
				(missileUp >= bottomSide) || (missileDown <= topSide))
			{
				delete missile;
				bullets[i] = nullptr;
				continue;
			}

			// Check if missile has hit an enemy or player, depending on who fired it
			if (missile->GetOwnerType() == PLAYER)
			{
				for (int32_t j = 0; j < ENEMY_MAX_ENEMIES; j++)
				{
					if (enemies[j] != nullptr)
					{
						Enemy *enemy = enemies[j];
						float_t enemyLeft = enemy->getPosition()->x - enemy->getWidth() / 2;
						float_t enemyRight = enemy->getPosition()->x + enemy->getWidth() / 2;
						float_t enemyUp = enemy->getPosition()->y - enemy->getHeight() / 2;
						float_t enemyDown = enemy->getPosition()->y + enemy->getHeight() / 2;

						if ((enemyLeft <= missileRight) && (enemyRight >= missileLeft) &&
							(enemyUp <= missileDown) && (enemyDown >= missileUp))
						{
							delete missile;
							bullets[i] = nullptr;
							delete enemy;
							enemies[j] = nullptr;
							break;
						}
					}
				}
			}
			else
			{
				float_t playerLeft = player->getPosition()->x - player->getWidth() / 2;
				float_t playerRight = player->getPosition()->x + player->getWidth() / 2;
				float_t playerUp = player->getPosition()->y - player->getHeight() / 2;
				float_t playerDown = player->getPosition()->y + player->getHeight() / 2;

				if ((playerLeft <= missileRight) && (playerRight >= missileLeft) &&
					(playerUp <= missileDown) && (playerDown >= missileUp))
				{
					delete missile;
					bullets[i] = nullptr;
					// TODO: Player got hit
					break;
				}
			}

		}
	}
}

void SpriteManager::spawnEnemy() {
    if (++indexEnemy == ENEMY_MAX_ENEMIES) {
        indexEnemy = 0;
    }

    if (enemies[indexEnemy] == nullptr) {
        enemies[indexEnemy] = new Enemy(ENEMY_PURPLE);
    }

    float_t bgWidth = (float_t) GameManager::GetInstance()->getBackgroundWidth();
	float_t bgHeight = (float_t) GameManager::GetInstance()->getBackgroundHeight();
    enemies[indexEnemy]->setPosition(getRangedRandom(-bgWidth / 2.0f, bgWidth / 2.0f), getRangedRandom(-bgHeight / 2.0f, bgHeight / 2.0f));
    enemies[indexEnemy]->setVelocity(0.0f, 0.0f);
}
