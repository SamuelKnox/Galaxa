#include "Entity.h"



Entity::Entity(char* entityID, float x, float y)
{
	id = entityID;
	SetPosition(x, y);
}


Entity::~Entity()
{
}

void Entity::Update(float elapsedTime) {

}

void Entity::SetPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

Entity::Position Entity::GetPosition() {
	return position;
}