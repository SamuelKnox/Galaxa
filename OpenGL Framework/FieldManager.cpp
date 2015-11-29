#define FIELD_MANAGER_CPP

#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
 
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "field.h"
#include "FieldManager.h"
#include "stateManager.h"

FieldManagerC* FieldManagerC::sInstance=NULL;


FieldManagerC *FieldManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new FieldManagerC();
	return sInstance;
}
void FieldManagerC::init()
{
	border = new FieldC(0.0f, -150.0f, 125.0f, 600.0f, 0x00FF0000, StateManagerC::FOUR_DIAMOND_PITS);

	/*holes[0] = new FieldC(-126.0f, -44.0f, 12.0f, 48.0f, 0x00000000, StateManagerC::FOUR_DIAMOND_PITS);
	holes[1] = new FieldC(-126.0f, 84.0f, 12.0f, 48.0f, 0x00000000, StateManagerC::FOUR_DIAMOND_PITS);
	holes[2] = new FieldC(130.0f, -44.0f, 12.0f, 48.0f, 0x00000000, StateManagerC::FOUR_DIAMOND_PITS);
	holes[3] = new FieldC(130.0f, 84.0f, 12.0f, 48.0f, 0x00000000, StateManagerC::FOUR_DIAMOND_PITS);

	holes[4] = new FieldC(-154.0f, 18.0f, 56, 24, 0x00000000, StateManagerC::WIDE_DIAMOND_PITS);
	holes[5] = new FieldC(151.0f, 18.0f, 56, 24, 0x00000000, StateManagerC::WIDE_DIAMOND_PITS);
	holes[6] = new FieldC(-2.0f, 68.0f, 10, 32, 0x00000000, StateManagerC::WIDE_DIAMOND_PITS);
	holes[7] = new FieldC(-2.0f, -32.0f, 10, 32, 0x00000000, StateManagerC::WIDE_DIAMOND_PITS);

	holes[8] = new FieldC(-136.0f, -34.0f, 6, 40, 0x00000000, StateManagerC::ARROW_PITS);
	holes[9] = new FieldC(136.0f, -34.0f, 6, 40, 0x00000000, StateManagerC::ARROW_PITS);
	holes[10] = new FieldC(-136.0f, 62.0f, 14, 40, 0x00000000, StateManagerC::ARROW_PITS);
	holes[11] = new FieldC(136.0f, 62.0f, 14, 40, 0x00000000, StateManagerC::ARROW_PITS);

	holes[12] = new FieldC(-140.0f, 30.0f, 15.0f, 50.0f, 0x00000000, StateManagerC::EIGHT_PITS);
	holes[13] = new FieldC(-20.0f, -70.0f, 15.0f, 50.0f, 0x00000000, StateManagerC::EIGHT_PITS);
	holes[14] = new FieldC(-15.0f, 100.0f, 15.0f, 50.0f, 0x00000000, StateManagerC::EIGHT_PITS);
	holes[15] = new FieldC(120.0f, 15.0f, 15.0f, 50.0f, 0x00000000, StateManagerC::EIGHT_PITS);*/
}
FieldC *FieldManagerC::getFieldPtr()
{
	return border;
}
void FieldManagerC::renderField()
{
	border->render();
	/*for (int32_t i = 0; i < NUM_HOLES; i++) {
		if (holes[i]->activeState == StateManagerC::GetInstance()->getState()) {
			holes[i]->render();
		}
	}*/
}
void FieldManagerC::shutdown()
{
	delete border;
}