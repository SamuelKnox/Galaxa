#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include "Collidable.h"

class Movable : public Collidable
{

public:
	Movable();
	~Movable();

	virtual void Update();

	Vector2D GetVelocity() { return velocity;  }
	void SetVelocity(float initX, float initY) { velocity.x = initX; velocity.y = initY; }

private:
	void UpdatePosition();

	Vector2D velocity;
};

#endif