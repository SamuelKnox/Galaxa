#include "Movable.h"

Movable::Movable()
{
}


Movable::~Movable()
{
}

void Movable::Update() {
	Collidable::Update();
	UpdatePosition();
}

void Movable::UpdatePosition() {
	Vector2D oldPosition = GetPosition();
	float newX = oldPosition.x + velocity.x;
	float newY = oldPosition.y + velocity.y;

	SetPosition(newX, newY);
}
