#include <windows.h>											// Header File For Windows
#include "baseTypes.h"
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <math.h>
//#include <stdlib.h>
#include <stdio.h>
#include "gamedefs.h"

const float DEG2RAD = 3.14159f/180.0f;


void DrawCircle(float_t radius, float_t x, float_t y, char8_t r, char8_t g, char8_t b, bool filled)
{
	
	glEnable(GL_POINT_SMOOTH);
	if(!filled)
	{
		glDisable(GL_TEXTURE_2D);
		glColor4ub(r, g, b, 0x20);
		// Set the point size
		glPointSize(1.0);
		glBegin(GL_POINTS);
		GLfloat radiusMax = radius + 2.0f;
		GLfloat radiusMin = radius - 2.0f;
		for (int32_t i = 0; i < 360; i += 3)
		{
			GLfloat degInRad = i*DEG2RAD;
			#pragma warning(disable : 4244)
			glVertex2f(x + (cos(degInRad)*radius),		y + (sin(degInRad)*radius));
			glVertex2f(x + (cos(degInRad)*radiusMax),	y + (sin(degInRad)*radiusMax));
			glVertex2f(x + (cos(degInRad)*radiusMin),	y + (sin(degInRad)*radiusMin));
		}
		glEnd();
	}
	else
	{
	    glColor4ub(r, g, b,0xFF);
		glEnable(GL_BLEND); 
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		glPointSize(radius/2.0f);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
}

void DrawLine(float_t startX, float_t startY, float_t endX, float_t endY, char8_t r, char8_t g, char8_t b)
{
	glColor3ub(r, g, b);
	// Draw filtered lines
	glEnable(GL_LINE_SMOOTH);

	glLineWidth(LINE_WIDTH);

	glBegin(GL_LINE_STRIP);
		glVertex2f(startX, startY);
		glVertex2f(endX, endY);
	glEnd();

}

void DrawSprite(GLuint spriteID, bool8_t isFlipped,
				float_t xPosLeft, float_t xPosRight, 
				float_t yPosTop, float_t yPosBot,
				float_t xTexCoord, float_t numSprites)
{

	GLfloat xTexCoordLeft = xTexCoord;
	GLfloat xTexCoordRight = xTexCoord;

	if (isFlipped)
	{
		xTexCoordLeft += (1.0f / numSprites);
	}
	else
	{
		xTexCoordRight += (1.0f / numSprites);
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteID);
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glBegin(GL_QUADS);
	{		
		// Top-Left
		glTexCoord2f(xTexCoordLeft, 0.0f);
		glVertex3f(xPosLeft, yPosTop, 0.0f);

		// Top-Right
		glTexCoord2f(xTexCoordRight, 0.0f);
		glVertex3f(xPosRight, yPosTop, 0.0f);

		// Bot-Right
		glTexCoord2f(xTexCoordRight, 1.0f);
		glVertex3f(xPosRight, yPosBot, 0.0f);

		// Bot-Left
		glTexCoord2f(xTexCoordLeft, 1.0f);
		glVertex3f(xPosLeft, yPosBot, 0.0f);
		
	}	
	glEnd();
}
