#ifndef _SHAPE_DRAW_H
#define _SHAPE_DRAW_H

void DrawCircle(float_t radius, float_t x, float_t y, 
				char8_t r, char8_t g, char8_t b, bool filled);

void DrawLine(float_t startX, float_t startY, float_t endX, float_t endY, 
			  char8_t r, char8_t g, char8_t b);

void DrawBackground(GLuint backgroundID, float_t width, float_t height, 
					float_t yTexCoord, uint32_t numSprites);

void DrawSprite(GLuint spriteID, bool8_t isFlipped, float_t xPosLeft, float_t xPosRight,
				float_t yPosTop, float_t yPosBot, float_t xTexCoord, uint32_t numSprites);

#endif