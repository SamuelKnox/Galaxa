#ifndef _SPRITE_MANAGER_H
#define _SPRITE_MANAGER_H

class SpriteManager
{
public:
	static SpriteManager *CreateInstance();
	static SpriteManager *GetInstance() { return sInstance; };
	~SpriteManager() {};

	void	init();
	void	shutdown();
	void	updateSprites(DWORD milliseconds);
	void	renderSprites();
	ET* getET();

private:
	SpriteManager() {};
	static SpriteManager *sInstance;

	ET* player;
	bool8_t CheckCollisions();
};

#endif
