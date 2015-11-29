#ifndef _SPRITE_MANAGER_H
#define _SPRITE_MANAGER_H

#include "gamedefs.h"
#include "baseTypes.h"
#include "Enemy.h"
#include "ET.h"

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

private:
	SpriteManager() {};
	static SpriteManager *sInstance;

	ET* player;

    Enemy* enemies[ENEMY_MAX_ENEMIES] = { nullptr };
    uint32_t enemiesCount = 0;

	bool8_t CheckCollisions();

    void spawnEnemy();
    DWORD lastSpawnDuration = 0;
    unsigned indexEnemy = 0;
};

#endif
