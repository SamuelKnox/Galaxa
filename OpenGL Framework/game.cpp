#define GAME_CPP
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include "jsy/jsy.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collInfo.h"
#include "object.h"
#include "Sprite.h"
#include "field.h"
#include "random.h"
#include "openGLStuff.h"
#include "SpriteManager.h"
#include "FieldManager.h"
#include "GameManager.h"
#include "SoundManager.h"

#include "game.h"

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
    JsyGOpen(&jsyGHandle);
    JsyInputOpen(&jsyInputHandle);

	SpriteManager::CreateInstance();
	FieldManagerC::CreateInstance();
	GameManager::CreateInstance();
    SoundManager::CreateInstance();

	GameManager::GetInstance()->init(BG_WIDTH, BG_HEIGHT);
	FieldManagerC::GetInstance()->init();
	SpriteManager::GetInstance()->init();
    SoundManager::GetInstance()->init();
}

void CGame::UpdateFrame(uint32_t milliseconds)
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
	GameManager::GetInstance()->shutdown();
}

void CGame::DestroyGame(void)
{
	delete SpriteManager::GetInstance();
	delete FieldManagerC::GetInstance();	
	delete GameManager::GetInstance();
}
