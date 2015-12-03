
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
	lastSpawnDuration = 0;
	indexEnemy = 0;

	// Setup scoreboard & set gameState to title screen
	scoreboard = new Scoreboard();
	mGameState = TITLE_SCREEN;

	for (int32_t i = 0; i < MAX_LEVEL_DIGITS; i++)
	{
		levelDisplay[i] = new Sprite(LEVEL_X + NUMBER_WIDTH * -i, LEVEL_Y, NUMBER_WIDTH, NUMBER_HEIGHT, SpriteManager::NUMBERS, 0, NUMBER_NUM_SPRITES);
	}
}
 
void GameManager::shutdown()
{
	delete scoreboard;

	for (int32_t i = 0; i < MAX_LEVEL_DIGITS; i++)
	{
		delete levelDisplay[i];
	}
}

void GameManager::render()
{
    // Draw background and scoreboard (if in game)
    JsyGDrawBackGround(CGame::GetInstance()->GetJsyGHandle(), mCurrentBackground, (float_t) mBackgroundWidth, (float_t) mBackgroundHeight, mBackgroundOffset, mBackgroundNumSprites);

	if (mGameState == IN_GAME) {
		scoreboard->Render();

		for (int32_t i = 0; i < MAX_LEVEL_DIGITS; i++)
		{
			double_t placeVal = pow(10, -i);
			int32_t digit = (int32_t)(mLevelNum * placeVal) % 10;
			levelDisplay[i]->setCurrentSprite(digit);
			levelDisplay[i]->render();
		}
	}
}

void GameManager::update(uint32_t milliseconds)
{
	// Check for user input if at title or gameover screens
	checkForInput();

	// Update background offset for scrolling
	updateBackground(milliseconds);

	// Spawn enemies for current wave 
	lastSpawnDuration += milliseconds;
	if ((mEnemiesLeftInWave > 0) && (lastSpawnDuration >= ENEMY_RESPAWN_TIME_MILLISEC))
	{
		lastSpawnDuration = 0;
		if (++indexEnemy == ENEMY_MAX_ENEMIES)
		{
			indexEnemy = 0;
		}
		SpriteManager::GetInstance()->spawnEnemy(indexEnemy);
		mEnemiesLeftInWave--;
		mEnemiesAlive++;
	}

	// Update waves and level progression
	updateLevelWaves();
}

int32_t GameManager::getState()
{
	return mGameState;
}

void GameManager::enemyKilled(int32_t pointValue)
{
	mEnemiesAlive--;	
	scoreboard->score += pointValue;
}

void GameManager::setState(int32_t state)
{
	mGameState = state;
}

void GameManager::startNewGame()
{
	// Initialize game logic variables
	mLevelNum = 1;
	mWaveNum = 1;
	mWavesInLevel = 1;
	mEnemiesLeftInWave = BASE_ENEMIES_PER_WAVE;
	mEnemiesAlive = 0;
	lastSpawnDuration = 0;

	mGameState = IN_GAME;
	SpriteManager::GetInstance()->startGame();
	scoreboard->Reset();
}

void GameManager::checkForInput()
{
	// Check if space is pressed at title_screen to start game
	if (mGameState == TITLE_SCREEN)
	{
		SHORT startKey = GetKeyState(VK_SPACE);
		if ((startKey & 0x8000))
		{
			startNewGame();
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

void GameManager::updateBackground(uint32_t milliseconds)
{
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

void GameManager::updateLevelWaves()
{
	// Check if there are any enemies left in current wave
	if (mEnemiesLeftInWave == 0 && mEnemiesAlive == 0)
	{
		mWaveNum++;

		// If last wave for level, then transition to next level
		if (mWaveNum > mWavesInLevel)
		{
			mLevelNum++;
			mWaveNum = 1;
			mWavesInLevel = 1 + (mLevelNum / 5);
		}

		// Reset enemy count
		mEnemiesLeftInWave = BASE_ENEMIES_PER_WAVE + (mLevelNum / 5);
	}

	char str[256];
	sprintf_s(str, "Level: %d, Wave: %d , Enemies Alive: %d, Enemies Left in Wave: %d \n", mLevelNum, mWaveNum, mEnemiesAlive, mEnemiesLeftInWave);
	OutputDebugString(str);
}
