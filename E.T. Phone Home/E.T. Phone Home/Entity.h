#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "common.h"

class Entity
{

public:
	Entity();
	Entity(float_t initX, float_t initY);
	~Entity() { }

	virtual void Update();

	Vector2D GetPosition() { return position;  }
	void SetPosition(float_t initX, float_t initY) { position.x = initX; position.y = initY; }

private:
	Vector2D position;

};

#endif