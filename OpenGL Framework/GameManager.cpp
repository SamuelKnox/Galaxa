
#define STATE_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <assert.h>

#include "baseTypes.h"
#include "gamedefs.h"
#include "stateManager.h"
#include "openglframework.h"
#include "soil.h"

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
	mBackgroundHeight = height;
	mBackgroundWidth = width;

	// Load background texture maps
	mBackgroundTextureMaps = (GLuint *)malloc(NUM_BACKGROUNDS * sizeof(GLuint));

	mBackgroundTextureMaps[StateManagerC::FOREST] = SOIL_load_OGL_texture(BG_FOREST, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}
void GameManager::shutdown()
{

}
void GameManager::render()
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mCurrentBackground);

	// Draw background for current level
	glBegin(GL_QUADS);
	{
		glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(-mBackgroundWidth / 2, -mBackgroundHeight / 2, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(mBackgroundWidth / 2, -mBackgroundHeight / 2, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(mBackgroundWidth / 2, mBackgroundHeight / 2, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-mBackgroundWidth / 2, mBackgroundHeight / 2, 0.0f);
	}
	
	glEnd();

}
void GameManager::update(DWORD milliseconds)
{
	mCurrentTime += milliseconds;

	int32_t currentState = StateManagerC::GetInstance()->getState();
	mCurrentBackground = mBackgroundTextureMaps[currentState];

	// TODO: setup title screen and manage scoreboard stuff
}