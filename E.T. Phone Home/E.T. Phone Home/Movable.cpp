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
	Position oldPosition = GetPosition();
	float newX = oldPosition.x + velocity.x * speed;
	float newY = oldPosition.y + velocity.y * speed;
	SetPosition(newX, newY);
}

void Movable::SetVelocity(float x, float y) {
	velocity.x = x;
	velocity.y = y;
}

Movable::Velocity Movable::GetVelocity() {
	return velocity;
}