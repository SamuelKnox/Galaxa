#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Scoreboard.h"

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
	void		update(uint32_t milliseconds);
	void		render();
	void		shutdown();

	void		setState(int32_t stateToSet);
	int32_t		getState();
	int32_t		getBackgroundWidth() { return mBackgroundWidth; }
	int32_t		getBackgroundHeight() { return mBackgroundHeight; }

	Scoreboard* scoreboard;

private:
	static GameManager *sInstance;
	GameManager() {};

	void checkForInput();

    uint32_t mTitleScreenBackground;
    uint32_t mSpaceBackground;
    uint32_t mCurrentBackground;

	int32_t mGameState;

	int32_t mBackgroundWidth;
	int32_t mBackgroundHeight;
	int32_t mBackgroundNumSprites;
	float_t mBackgroundOffset;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;

};

#endif