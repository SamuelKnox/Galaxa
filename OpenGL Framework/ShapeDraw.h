

void DrawCircle(float_t radius, float_t x, float_t y, 
				char8_t r, char8_t g, char8_t b, bool filled);

void DrawLine(float_t startX, float_t startY, 
		      float_t endX, float_t endY, 
			  char8_t r, char8_t g, char8_t b);

void DrawSprite(GLuint spriteID, bool8_t isFlipped,
	float_t xPosLeft, float_t xPosRight,
	float_t yPosTop, float_t yPosBot,
	float_t xTexCoord, float_t numSprites);