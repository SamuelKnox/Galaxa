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
	enum GAME_OBJECTS
	{
		PLAYER,
		ENEMY_GREEN,
		ENEMY_PURPLE,
		BULLET,
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

private:
	SpriteManager() {};
	static SpriteManager *sInstance;

	GLuint *spriteTextureMaps;
	ET* player;
    Enemy* enemies[ENEMY_MAX_ENEMIES] = { nullptr };

    void spawnEnemy();
    DWORD lastSpawnDuration = 0;
    unsigned indexEnemy = 0;

	Bullet** bullets;

	void CheckBulletCollisions();
};

#endif
