#pragma once
class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	Entity* CreateEntity();
};