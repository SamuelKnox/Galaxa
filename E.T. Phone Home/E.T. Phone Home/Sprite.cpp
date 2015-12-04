#include "Sprite.h"

Sprite::Sprite()
{
	imagePath = nullptr;
	width = 0.0f;
	height = 0.0f;
}

Sprite::Sprite(char8_t *path, float_t initWidth, float_t initHeight)
{
	imagePath = path;
	width = initWidth;
	height = initHeight;
}

Sprite::~Sprite()
{
}

void Sprite::Draw() {
	//RendererManager.Draw(imagePath, GetPosition());
}