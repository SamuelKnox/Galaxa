#define SPRITE_MANAGER_CPP
#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>	// Header File For Variable Argument Routines
#include <math.h>	// Header File For Math Operations
#include <gl\gl.h>	// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library

#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "Sprite.h"
#include "ET.h"
#include "random.h"
#include "field.h"
#include "FieldManager.h"
#include "stateManager.h"
#include "SpriteManager.h"


SpriteManager* SpriteManager::sInstance = NULL;


SpriteManager *SpriteManager::CreateInstance()
{
	assert(sInstance == NULL);
	sInstance = new SpriteManager();
	return sInstance;
}

void SpriteManager::init()
{
	printf("Initing the SpriteManager.\n");

	player = (ET*)malloc(sizeof(ET));
	player = new ET(0.0f, -500.0f, 0.0f, 0.0f);
	player->setID(0);
}

void SpriteManager::updateSprites(DWORD milliseconds)
{
	player->update(milliseconds);

	// TODO: Make this transition to a different level/background
	if (CheckCollisions()) {
		exit(0);
	}
}

ET* SpriteManager::getET()
{
	return player;
}

void SpriteManager::renderSprites()
{
	player->render();
}
void SpriteManager::shutdown()
{
	delete player;

}

bool8_t SpriteManager::CheckCollisions()
{
	for (int32_t i = 0; i < NUM_HOLES; i++) {
		// Check if player & holes collide
		FieldC* field = FieldManagerC::GetInstance()->holes[i];

		if (field->activeState == StateManagerC::GetInstance()->getState()) {
			bool8_t left = field->getPosition()->x + field->getWidth() < player->getPosition()->x;
			bool8_t right = field->getPosition()->x > player->getPosition()->x + player->getWidth();
			bool8_t up = field->getPosition()->y + field->getHeight() < player->getPosition()->y;
			bool8_t down = field->getPosition()->y > player->getPosition()->y + player->getHeight();

			if (!(left || right || up || down)) {
				return true;
			}
		}
	}
	return false;
}
