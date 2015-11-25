#include "Sprite.h"



Sprite::Sprite(char* spriteID, float x, float y, char* image) : Entity(spriteID, x, y)
{
	imagePath = image;
}


Sprite::~Sprite()
{
}

void Sprite::Draw() {
	if (!shouldDraw) {
		return;
	}
	//RendererManager.Draw(imagePath, GetPosition());
}

float Sprite::GetWidth() {
	return width;
}

float Sprite::GetHeight() {
	return height;
}

void Sprite::SetShouldDraw(bool draw) {
	shouldDraw = draw;
}

bool Sprite::GetShouldDraw() {
	return shouldDraw;
}