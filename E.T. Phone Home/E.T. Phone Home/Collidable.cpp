#include "Collidable.h"

Collidable::Collidable()
{
}


Collidable::~Collidable()
{
}

bool8_t Collidable::IsColliding(Collidable other) {
	bool right = other.GetPosition().x > GetPosition().x + GetWidth();
	bool left = other.GetPosition().x + other.GetWidth() < GetPosition().x;
	bool up = other.GetPosition().y + other.GetHeight() < GetPosition().y;
	bool down = other.GetPosition().y > GetPosition().y + GetHeight();

	return right || left || up || down;
}