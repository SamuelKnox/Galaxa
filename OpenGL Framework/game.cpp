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

	//BallManagerC::CreateInstance();
	SpriteManager::CreateInstance();
	StateManagerC::CreateInstance();
	FieldManagerC::CreateInstance();
	InputManagerC::CreateInstance();
	SpriteDemoManagerC::CreateInstance();

	InputManagerC::GetInstance()->init();

	//BallManagerC::GetInstance()->init();
	SpriteManager::GetInstance()->init();
	StateManagerC::GetInstance()->setState(StateManagerC::PIT);
	FieldManagerC::GetInstance()->init();
	SpriteDemoManagerC::GetInstance()->init(28,26);
}
void CGame::UpdateFrame(DWORD milliseconds)			
{
	keyProcess();
	SpriteDemoManagerC::GetInstance()->updateSprites(milliseconds);
	//BallManagerC::GetInstance()->updateBalls(milliseconds);
	SpriteManager::GetInstance()->updateSprites(milliseconds);
	InputManagerC::GetInstance()->update();
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();
	//BallManagerC::GetInstance()->renderBalls();
	SpriteDemoManagerC::GetInstance()->renderSprites();
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
	//BallManagerC::GetInstance()->shutdown();
	SpriteManager::GetInstance()->shutdown();
	StateManagerC::GetInstance()->shutdown();
	FieldManagerC::GetInstance()->shutdown();
	SpriteDemoManagerC::GetInstance()->shutdown();
}
void CGame::DestroyGame(void)
{
	//delete BallManagerC::GetInstance();	
	delete SpriteManager::GetInstance();
	delete StateManagerC::GetInstance();	
	delete FieldManagerC::GetInstance();	
}