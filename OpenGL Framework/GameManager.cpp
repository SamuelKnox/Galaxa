
#define STATE_MANAGER_CPP
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <assert.h>
#include <iostream>

#include "jsy/jsy.h"
#include "gamedefs.h"
#include "stateManager.h"
#include "SpriteManager.h"
#include "openglframework.h"
#include "Scoreboard.h"
#include "jsy/jsy.h"
#include "game.h"
#include "GameManager.h"


GameManager* GameManager::sInstance = NULL;


GameManager *GameManager::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else
		sInstance = new GameManager();
	return sInstance;
}

void GameManager::init(int32_t width, int32_t height)
{
	// Load background texture maps
	JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), BG_TITLE_SCREEN, &mTitleScreenBackground);
	JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), BG_SPACE, &mSpaceBackground);

	// Initialize background variables
	mCurrentBackground = mTitleScreenBackground;
	mBackgroundWidth = width;
	mBackgroundHeight = height;
	mBackgroundOffset = 0.0f;
	mBackgroundNumSprites = TITLE_NUM_SPRITES;

	// Setup scoreboard and set gameState to title_screen
	mGameState = TITLE_SCREEN;
	scoreboard = new Scoreboard();
}

void GameManager::shutdown()
{
	delete scoreboard;
}

void GameManager::render()
{
    // Draw background and scoreboard (if in game)
    JsyGDrawBackGround(CGame::GetInstance()->GetJsyGHandle(), mCurrentBackground, (float_t) mBackgroundWidth, (float_t) mBackgroundHeight, mBackgroundOffset, mBackgroundNumSprites);

	if (mGameState == IN_GAME) {
		scoreboard->Render();
	}
}

void GameManager::update(uint32_t milliseconds)
{
	// Check for user input if at title or gameover screens
	checkForInput();

	// Update background if state has changed
	if (mGameState == TITLE_SCREEN && mCurrentBackground != mTitleScreenBackground)
	{
		mCurrentBackground = mTitleScreenBackground;
		mBackgroundOffset = 0.0f;
		mBackgroundNumSprites = TITLE_NUM_SPRITES;
	}
	else if (mGameState == IN_GAME && mCurrentBackground != mSpaceBackground)
	{
		mCurrentBackground = mSpaceBackground;
		mBackgroundOffset = 0.0f;
		mBackgroundNumSprites = SPACE_NUM_SPRITES;
	}

	// Check if offset should be updated for scrolling
	if (mBackgroundNumSprites > 1)
	{
		mBackgroundOffset = mBackgroundOffset + (milliseconds * SCROLL_RATE / 1000.0f);
		if (mBackgroundOffset > 1.0f / NUM_BACKGROUNDS)
		{
			//mBackgroundOffset = mBackgroundOffset - 1.0f / NUM_BACKGROUNDS;
			mBackgroundOffset = 0.0f;
		}
	}
}

int32_t GameManager::getState()
{
	return mGameState;
}
void GameManager::setState(int32_t state)
{
	mGameState = state;
}

void GameManager::checkForInput()
{
	// Check if space is pressed at title_screen to start game
	if (mGameState == TITLE_SCREEN)
	{
		SHORT startKey = GetKeyState(VK_SPACE);
		if ((startKey & 0x8000))
		{
			mGameState = IN_GAME;
			SpriteManager::GetInstance()->startGame();
			scoreboard->Reset();
		}
	}

	// Check if enter is pressed during gameover to return to title_screen
	else if (mGameState == GAME_OVER)
	{
		SHORT startKey = GetKeyState(VK_RETURN);
		if ((startKey & 0x8000))
		{
			mGameState = TITLE_SCREEN;
			SpriteManager::GetInstance()->resetGame();
		}
	}
}
