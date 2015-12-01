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
		POINTS,
		GAMEOVER,
		NUM_OBJECTS
	};

	enum POINT_TYPES
	{
		POINTS_150,
		POINTS_500,
		POINTS_800,
		POINTS_1000,
		POINTS_1500,
		POINTS_1600,
		POINTS_2000,
		POINTS_3000,
		POINTS_NONE
	};

	static SpriteManager *CreateInstance();
	static SpriteManager *GetInstance() { return sInstance; };
	~SpriteManager();

	void	init();
	void	shutdown();
	void	updateSprites(DWORD milliseconds);
	void	renderSprites();
	GLuint getSpriteTextureMap(int32_t objectType);
	void	resetGame();
	void	startGame();
	void	endGame();

	ET* getET();
	void CreateBullet(float_t x, float_t y, float_t xVel, float_t yVel, int32_t ownerType);
	void CreateExplosion(float_t x, float_t y, uint32_t explosionType, uint32_t pointType);

private:
	SpriteManager() {};
	static SpriteManager *sInstance;

	GLuint *spriteTextureMaps;
	bool8_t mInGame;

	// GameObjects
	ET* player = nullptr;
	Bullet* bullets[MAX_NUM_MISSILES] = { nullptr };
    Enemy* enemies[ENEMY_MAX_ENEMIES] = { nullptr };
	Explosion* explosions[MAX_EXPLOSIONS] = { nullptr };
	Sprite* gameOver = nullptr;

	// Collsions
	void CheckBoundaryCollisions();
	void CheckBulletCollisions();
	bool8_t CheckSpriteHitBoundaries(Sprite *sprite);
	bool8_t CheckSpriteCollision(Sprite *sprite1, Sprite *sprite2);

	// Enemies
    void spawnEnemy();
    DWORD lastSpawnDuration = 0;
    unsigned indexEnemy = 0;	
};

#endif
