#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class GameManager
{
public:
	static GameManager	*CreateInstance();
	static GameManager	*GetInstance() { return sInstance; };
	~GameManager() {};

	void		init(int32_t backgroundWidth, int32_t backgroundHeight);
	void		update(DWORD milliseconds);
	void		render();
	void		shutdown();

	int32_t			getBackgroundWidth() { return mBackgroundWidth; }
	int32_t			getBackgroundHeight() { return mBackgroundHeight; }


private:
	static GameManager *sInstance;
	GameManager() {};

	GLuint *mBackgroundTextureMaps;
	GLuint mCurrentBackground;

	int32_t mBackgroundWidth;
	int32_t mBackgroundHeight;

	float_t mBackgroundOffset;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;

};

#endif