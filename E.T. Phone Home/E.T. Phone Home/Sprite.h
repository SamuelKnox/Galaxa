#pragma once
#include "Entity.h"
class Sprite :
	public Entity
{
public:
	Sprite(char* id, float x, float y, char* imagePath);
	~Sprite();
	virtual void Draw();
	float GetWidth();
	float GetHeight();
	void SetShouldDraw(bool draw);
	bool GetShouldDraw();

private:
	char* imagePath;
	float width;
	float height;
	bool shouldDraw;
};

