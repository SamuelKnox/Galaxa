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
#include "FallTrajectory.h"
#include "SoundManager.h"

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

	spriteTextureMaps[EXPLOSION_PLAYER] = SOIL_load_OGL_texture(EXPLOSION_PLAYER_SPRITE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	spriteTextureMaps[EXPLOSION_ENEMY] = SOIL_load_OGL_texture(EXPLOSION_ENEMY_SPRITE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	spriteTextureMaps[POINTS] = SOIL_load_OGL_texture(POINTS_SPRITES, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	spriteTextureMaps[GAMEOVER] = SOIL_load_OGL_texture(GAMEOVER_SPRITE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mInGame = false;

	player = new ET(0.0f, 0.0f, 0.0f, 0.0f, PLAYER);
    player->setFireSfxId(SoundManager::GetInstance()->LoadSound(PLAYER_SFX_FIRE));
}

void SpriteManager::updateSprites(DWORD milliseconds)
{
	if (!mInGame)
	{
		return;
	}

	player->update(milliseconds);
	player->updateET(milliseconds);
	for (int i = 0; i < MAX_NUM_MISSILES; i++) 
	{
		if (bullets[i] != nullptr) 
		{
			bullets[i]->update(milliseconds);
		}
	}

    for (int i = 0; i < ENEMY_MAX_ENEMIES; i++) 
	{
        if (enemies[i] != nullptr) 
		{
            enemies[i]->update(milliseconds);
        }
    }

	for (int i = 0; i < MAX_EXPLOSIONS; i++)
	{
		if (explosions[i] != nullptr)
		{
			if (explosions[i]->CycleExplosionAnimation(milliseconds))
			{
				delete explosions[i];
				explosions[i] = nullptr;
			}
		}
	}

    lastSpawnDuration += milliseconds;
    if (lastSpawnDuration >= ENEMY_RESPAWN_TIME_MILLISEC) 
	{
        lastSpawnDuration = 0;
        spawnEnemy();
    }

	CheckBoundaryCollisions();
	CheckBulletCollisions();
}

ET* SpriteManager::getET()
{
	return player;
}

void SpriteManager::renderSprites()
{
	if (gameOver != nullptr)
	{
		gameOver->render();
	}

	if (!mInGame)
	{
		return;
	}

	if (player != nullptr)
	{
		player->render();
	}

	for (int i = 0; i < MAX_NUM_MISSILES; i++) 
	{
		if (bullets[i] != nullptr) 
		{
			bullets[i]->render();
		}
	}

    for (int i = 0; i < ENEMY_MAX_ENEMIES; i++) 
	{
        if (enemies[i] != nullptr) 
		{
            enemies[i]->render();
        }
    }

	for (int i = 0; i < MAX_EXPLOSIONS; i++)
	{
		if (explosions[i] != nullptr)
		{
			explosions[i]->render();
		}
	}
}

GLuint SpriteManager::getSpriteTextureMap(int32_t objectType)
{
	return spriteTextureMaps[objectType];
}

void SpriteManager::shutdown()
{
	resetGame();

	free(spriteTextureMaps);
	free(bullets);
	free(enemies);
	free(explosions);
}

void SpriteManager::resetGame()
{
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}

	if (gameOver != nullptr)
	{
		delete gameOver;
		gameOver = nullptr;
	}

	for (int i = 0; i < MAX_NUM_MISSILES; i++)
	{
		if (bullets[i] != nullptr)
		{
			delete bullets[i];
			bullets[i] = nullptr;
		}
	}

	for (int i = 0; i < ENEMY_MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	for (int i = 0; i < MAX_EXPLOSIONS; i++)
	{
		if (explosions[i] != nullptr)
		{
			delete explosions[i];
			explosions[i] = nullptr;
		}
	}
}

void SpriteManager::startGame()
{
	resetGame();
	player = new ET(0.0f, 0.0f, 0.0f, 0.0f, PLAYER);
    player->setFireSfxId(SoundManager::GetInstance()->LoadSound(PLAYER_SFX_FIRE));
	mInGame = true;
}

void SpriteManager::endGame()
{
	gameOver = new Sprite(0.0f, 0.0f, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, GAMEOVER);
	mInGame = false;
	GameManager::GetInstance()->setState(GameManager::GAME_OVER);
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

void SpriteManager::CreateExplosion(float_t x, float_t y, uint32_t explosionType, uint32_t pointType)
{
	for (int i = 0; i < MAX_EXPLOSIONS; i++)
	{
		if (explosions[i] == nullptr)
		{
			explosions[i] = new Explosion(x, y, explosionType, pointType);
			break;
		}
	}
}

void SpriteManager::CheckBoundaryCollisions()
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
		}
	}

	// NOTE: this can be removed if enemies no longer just fall off screen
	for (int32_t j = 0; j < ENEMY_MAX_ENEMIES; j++)
	{
		if (enemies[j] != nullptr)
		{
			Enemy *enemy = enemies[j];
			float_t enemyLeft = enemy->getPosition()->x - enemy->getWidth() / 2;
			float_t enemyRight = enemy->getPosition()->x + enemy->getWidth() / 2;
			float_t enemyUp = enemy->getPosition()->y - enemy->getHeight() / 2;
			float_t enemyDown = enemy->getPosition()->y + enemy->getHeight() / 2;

			// Check if enemy is out of bounds
			if ((enemyLeft <= leftSide) || (enemyRight >= rightSide) ||
				(enemyUp >= bottomSide) || (enemyDown <= topSide))
			{
				delete enemy;
				enemies[j] = nullptr;
				continue;
			}
		}
	}
}

void SpriteManager::CheckBulletCollisions()
{
	for (int32_t i = 0; i < MAX_NUM_MISSILES; i++)
	{
		if (bullets[i] != nullptr)
		{
			Bullet *missile = bullets[i];
			float_t missileLeft = missile->getPosition()->x - missile->getWidth() / 2;
			float_t missileRight = missile->getPosition()->x + missile->getWidth() / 2;
			float_t missileUp = missile->getPosition()->y - missile->getHeight() / 2;
			float_t missileDown = missile->getPosition()->y + missile->getHeight() / 2;

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
							CreateExplosion(enemy->getPosition()->x, enemy->getPosition()->y, EXPLOSION_ENEMY, POINTS_500);
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
					CreateExplosion(player->getPosition()->x, player->getPosition()->y, EXPLOSION_PLAYER, POINTS_NONE);
					endGame();
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
        enemies[indexEnemy] = new Enemy();
        static uint32_t id = SoundManager::GetInstance()->LoadSound(ENEMY_SFX_KILL);
        enemies[indexEnemy]->setKillSfxId(id);
    }

    float_t bgWidth = (float_t) GameManager::GetInstance()->getBackgroundWidth() - enemies[indexEnemy]->getWidth();
	float_t bgHeight = (float_t) GameManager::GetInstance()->getBackgroundHeight() - enemies[indexEnemy]->getHeight();
    enemies[indexEnemy]->setPosition(getRangedRandom(-bgWidth / 2.0f, bgWidth / 2.0f), getRangedRandom(0.0f, bgHeight / 2.0f));
    enemies[indexEnemy]->setSpriteType(getRangedRandom(ENEMY_GREEN, ENEMY_PURPLE));
    enemies[indexEnemy]->reset();
}
