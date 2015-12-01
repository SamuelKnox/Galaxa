#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
 
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collInfo.h"
#include "object.h"
#include "ball.h"
#include "Sprite.h"
#include "field.h"
#include "random.h"
#include "gameObjects.h"
#include "openGLStuff.h"
#include "game.h"
#include "StateManager.h"
#include "BallManager.h"
#include "SpriteManager.h"
#include "FieldManager.h"
#include "InputManager.h"
#include "SpriteDemoManager.h"
#include "GameManager.h"
#include "SoundManager.h"

// Declarations
const char8_t CGame::mGameTitle[]="Framework1";
CGame* CGame::sInstance=NULL;
BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;						
}

void CGame::init()
{
	SpriteManager::CreateInstance();
	FieldManagerC::CreateInstance();
	StateManagerC::CreateInstance();
	GameManager::CreateInstance();
    SoundManager::CreateInstance();

	GameManager::GetInstance()->init(BG_WIDTH, BG_HEIGHT);
	StateManagerC::GetInstance()->setState(StateManagerC::SPACE);
	FieldManagerC::GetInstance()->init();
	SpriteManager::GetInstance()->init();
    SoundManager::GetInstance()->init();
}
void CGame::UpdateFrame(DWORD milliseconds)			
{
	keyProcess();
	GameManager::GetInstance()->update(milliseconds);
	SpriteManager::GetInstance()->updateSprites(milliseconds);
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();
	GameManager::GetInstance()->render();
	FieldManagerC::GetInstance()->renderField();
	SpriteManager::GetInstance()->renderSprites();
}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
	SpriteManager::GetInstance()->shutdown();
	FieldManagerC::GetInstance()->shutdown();
	StateManagerC::GetInstance()->shutdown();
	GameManager::GetInstance()->shutdown();
}
void CGame::DestroyGame(void)
{
	delete SpriteManager::GetInstance();
	delete StateManagerC::GetInstance();	
	delete FieldManagerC::GetInstance();	
	delete GameManager::GetInstance();
}
