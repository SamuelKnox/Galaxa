#pragma once
#include "Collidable.h"
class Movable :
	public Collidable
{
public:
	Movable();
	~Movable();
	virtual void Update();
	void SetVelocity(float x, float y);
	struct Velocity {
		float x;
		float y;
	} velocity;
	Velocity GetVelocity();

private:
	void UpdatePosition();
	float speed;
};