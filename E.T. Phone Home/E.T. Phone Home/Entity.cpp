#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::Update() {

}

void Entity::SetPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

Entity::Position Entity::GetPosition() {
	return position;
}