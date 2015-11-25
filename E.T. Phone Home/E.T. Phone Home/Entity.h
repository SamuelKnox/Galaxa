#pragma once
class Entity
{
public:
	Entity();
	~Entity();
	virtual void Update();
	void SetPosition(float x, float y);
	struct Position {
		float x;
		float y;
	} position;
	Position GetPosition();
};