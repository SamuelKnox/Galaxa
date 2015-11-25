#pragma once
#include "Collidable.h"
#include "Physics.h"
class Movable :
	public Collidable
{
public:
	Movable(char* movableID, float x, float y, char* image, float initialSpeed);
	~Movable();
	virtual void Update(float elapsedTime);
	void SetVelocity(float x, float y);
	struct Velocity {
		float x;
		float y;
	} velocity;
	Velocity GetVelocity();
	virtual void OnCollisionEnter(Collidable* collidable) = 0;

private:
	void UpdatePosition(float elapsedTime);
	float speed;
};