#ifndef _SPRITE_H
#define _SPRITE_H
#include "Object.h"

class Sprite : public ObjectC
{
public:
	Sprite();
	Sprite(float_t initPosX, float_t initPosY, float_t width, float_t height, int32_t gameObjectType);
	~Sprite();

	void update(uint32_t milliseconds);
	virtual void render();
	void disable() { mEnabled = false; };
	void enable() { mEnabled = true; };

	void setWidth(float_t width) { mWidth = width; }
	float_t getWidth() { return mWidth; }
	void setHeight(float_t height) { mHeight = height; }
	float_t getHeight() { return mHeight; }

	int32_t getType() { return mType; }

    virtual void setSpriteType(int32_t type);

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
