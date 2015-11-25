#pragma once
#include "Entity.h"
class Sprite :
	public Entity
{
public:
	Sprite();
	~Sprite();
	virtual void Draw();
	float GetWidth();
	float GetHeight();

private:
	char* imagePath;
	float width;
	float height;
};

