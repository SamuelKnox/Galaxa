#ifndef _SPRITE_MANAGER_H
#define _SPRITE_MANAGER_H

#include "ET.h"
#include "Bullet.h"
#include "gamedefs.h"
#include "baseTypes.h"
#include "Enemy.h"

class SpriteManager
{
public:
	static SpriteManager *CreateInstance();
	static SpriteManager *GetInstance() { return sInstance; };
	~SpriteManager();

	void	init();
	void	shutdown();
	void	updateSprites(DWORD milliseconds);
	void	renderSprites();
	ET* getET();
	void CreateBullet(float_t x, float_t y, float_t xVel, float_t yVel);

private:
	SpriteManager() {};
	static SpriteManager *sInstance;
	ET* player;
	Bullet* bullets[MAX_NUM_MISSILES];

    Enemy* enemies[ENEMY_MAX_ENEMIES] = { nullptr };
	bool8_t CheckCollisions();

    void spawnEnemy();
    DWORD lastSpawnDuration = 0;
    unsigned indexEnemy = 0;
};

#endif
