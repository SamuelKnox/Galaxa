#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class GameManager
{
public:
	enum STATES
	{
		TITLE_SCREEN,
		IN_GAME,
		GAME_OVER
	};

	static GameManager	*CreateInstance();
	static GameManager	*GetInstance() { return sInstance; };
	~GameManager() {};

	void		init(int32_t backgroundWidth, int32_t backgroundHeight);
	void		update(DWORD milliseconds);
	void		render();
	void		shutdown();

	void		setState(int32_t stateToSet);
	int32_t		getState();
	int32_t		getBackgroundWidth() { return mBackgroundWidth; }
	int32_t		getBackgroundHeight() { return mBackgroundHeight; }

private:
	static GameManager *sInstance;
	GameManager() {};

	void checkForInput();

	GLuint mTitleScreenBackground;
	GLuint mSpaceBackground;
	GLuint mCurrentBackground;

	int32_t mGameState;

	int32_t mBackgroundWidth;
	int32_t mBackgroundHeight;
	int32_t mBackgroundNumSprites;
	float_t mBackgroundOffset;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;

};

#endif