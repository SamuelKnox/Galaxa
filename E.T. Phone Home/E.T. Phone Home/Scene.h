#include "EntityFactory.h"

#pragma once
class Scene
{
public:
	Scene();
	~Scene();
	Entity* GetEntities();
	void AddEntity(Entity* entity);
	void UpdateEntities();
	void DrawSprites();

private:
	Entity* entities;
};