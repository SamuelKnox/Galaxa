#ifndef _SPRITE_MANAGER_H
#define _SPRITE_MANAGER_H

#include "ET.h"
#include "Bullet.h"
#include "gamedefs.h"
#include "baseTypes.h"
#include "Enemy.h"
#include "Explosion.h"

class SpriteManager
{
public:
	enum GAME_OBJECTS
	{
		PLAYER,
		ENEMY_GREEN,
		ENEMY_PURPLE,
		BULLET,
		EXPLOSION_PLAYER,
		EXPLOSION_ENEMY,
		NUM_OBJECTS
	};

	static SpriteManager *CreateInstance();
	static SpriteManager *GetInstance() { return sInstance; };
	~SpriteManager();

	void	init();
	void	shutdown();
	void	updateSprites(DWORD milliseconds);
	void	renderSprites();

	GLuint getSpriteTextureMap(int32_t objectType);

	ET* getET();
	void CreateBullet(float_t x, float_t y, float_t xVel, float_t yVel, int32_t ownerType);
	void CreateExplosion(float_t x, float_t y, int32_t explosionType);

private:
	SpriteManager() {};
	static SpriteManager *sInstance;

	GLuint *spriteTextureMaps;

	// GameObjects
	ET* player;
	Bullet* bullets[MAX_NUM_MISSILES] = { nullptr };
    Enemy* enemies[ENEMY_MAX_ENEMIES] = { nullptr };
	Explosion* explosions[MAX_EXPLOSIONS] = { nullptr };

    void spawnEnemy();
    DWORD lastSpawnDuration = 0;
    unsigned indexEnemy = 0;


	void CheckBoundaryCollisions();
	void CheckBulletCollisions();
};

#endif
