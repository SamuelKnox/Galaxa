#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Entity.h"

class Sprite :
	public Entity
{
public:
	Sprite();
	Sprite(char8_t *path, float_t initWidth, float_t initHeight);
	~Sprite();

	void Draw();
	float_t GetWidth() { return width; }
	float_t GetHeight() { return height; }

private:
	float_t width;
	float_t height;

	char8_t* imagePath;
	
};

#endif