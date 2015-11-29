#ifndef _SPRITE_H
#define _SPRITE_H
#include <windows.h>
#include <gl\gl.h>	
#include "Object.h"

class Sprite : public ObjectC
{
public:
	Sprite();
	~Sprite();

	void update(DWORD milliseconds);
	virtual void render();
	void disable() { mEnabled = false; };
	void enable() { mEnabled = true; };

	void setWidth(float_t width) { mWidth = width; }
	float_t getWidth() { return mWidth; }
	void setHeight(float_t height) { mHeight = height; }
	float_t getHeight() { return mHeight; }

protected:

	bool8_t mEnabled;
	bool8_t mIsFacingLeft;

	float_t mWidth;
	float_t mHeight;

	//GLuint mSpriteID;
	int32_t mType;
	int32_t numSprites;
	int32_t currentSprite;

};

#endif
