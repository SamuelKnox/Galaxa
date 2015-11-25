#include "Movable.h"



Movable::Movable(char* movableID, float x, float y, char* image, float initialSpeed) : Collidable(movableID, x, y, image)
{
	speed = initialSpeed;
}


Movable::~Movable()
{
}

void Movable::Update(float elapsedTime) {
	Collidable::Update(elapsedTime);
	UpdatePosition(elapsedTime);
	Collidable* collidable = Physics::SendMoveEvent(this);
	if (collidable != nullptr) {
		OnCollisionEnter(collidable);
	}
}

void Movable::UpdatePosition(float elapsedTime) {
	Position oldPosition = GetPosition();
	float newX = oldPosition.x + velocity.x * speed * elapsedTime;
	float newY = oldPosition.y + velocity.y * speed * elapsedTime;
	SetPosition(newX, newY);
}

void Movable::SetVelocity(float x, float y) {
	velocity.x = x;
	velocity.y = y;
}

Movable::Velocity Movable::GetVelocity() {
	return velocity;
}