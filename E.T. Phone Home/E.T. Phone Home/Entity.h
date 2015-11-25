#pragma once
class Entity
{
public:
	Entity(char* id, float x, float y);
	~Entity();
	virtual void Update(float elapsedTime);
	virtual void Draw() = 0;
	void SetPosition(float x, float y);
	struct Position {
		float x;
		float y;
	} position;
	Position GetPosition();
	char* id;
};