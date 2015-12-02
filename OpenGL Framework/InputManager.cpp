#include <iostream>
#include <windows.h>											// Header File For Windows
#include "jsy/jsy.h"
#include "InputManager.h"

InputManagerC* InputManagerC::sInstance = NULL;

InputManagerC *InputManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new InputManagerC();
	return sInstance;
}

void InputManagerC::update()
{
	/*SHORT keyLeft = GetKeyState(VK_LEFT);
	SHORT keyRight = GetKeyState(VK_RIGHT);
	SHORT keyUp = GetKeyState(VK_UP);
	SHORT keyDown = GetKeyState(VK_DOWN);

	Sprite *player = SpriteManager::GetInstance()->getET();

	if ((keyUp & 0x8000))
	{
		player->getVelocity()->y = -5.0f;
	}
	if ((keyDown & 0x8000))
	{
		player->getVelocity()->y = 5.0f;
	}
	if ((keyLeft & 0x8000))
	{
		player->getVelocity()->x = -5.0f;
	}
	if ((keyRight & 0x8000))
	{
		player->getVelocity()->x = 5.0f;
	}*/
}