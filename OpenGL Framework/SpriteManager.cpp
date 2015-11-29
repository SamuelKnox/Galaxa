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
#include "Bullet.h"
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

	player = new ET(0.0f, 0.0f, 0.0f, 0.0f);
	player->setID(0);

	for (int i = 0; i < MAX_NUM_BULLETS; i++) {
		bullets[i] = nullptr;
	}
}

void SpriteManager::updateSprites(DWORD milliseconds)
{
	player->update(milliseconds);
	player->updateET(milliseconds);
	for (int i = 0; i < MAX_NUM_BULLETS; i++) {
		if (bullets[i] != nullptr) {
			bullets[i]->update(milliseconds);
		}
	}

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
	for (int i = 0; i < MAX_NUM_BULLETS; i++) {
		if (bullets[i] != nullptr) {
			bullets[i]->render();
		}
	}
}
void SpriteManager::shutdown()
{
	delete player;

}

void SpriteManager::CreateBullet(float_t xVel, float_t yVel) {
	for (int i = 0; i < MAX_NUM_BULLETS; i++) {
		if (bullets[i] == nullptr) {
			bullets[i] = new Bullet();
			bullets[i]->setVelocity(xVel, yVel);
			bullets[i]->setID(1 + i);
			break;
		}
	}
}

bool8_t SpriteManager::CheckCollisions()
{
	//for (int32_t i = 0; i < NUM_HOLES; i++) {
	//	// Check if player & holes collide
	//	FieldC* field = FieldManagerC::GetInstance()->holes[i];

	//	if (field->activeState == StateManagerC::GetInstance()->getState()) {
	//		bool8_t left = field->getPosition()->x + field->getWidth() < player->getPosition()->x;
	//		bool8_t right = field->getPosition()->x > player->getPosition()->x + player->getWidth();
	//		bool8_t up = field->getPosition()->y + field->getHeight() < player->getPosition()->y;
	//		bool8_t down = field->getPosition()->y > player->getPosition()->y + player->getHeight();

	//		if (!(left || right || up || down)) {
	//			return true;
	//		}
	//	}
	//}
	return false;
}
