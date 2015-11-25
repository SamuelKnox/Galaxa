#pragma once
class Scene
{
public:
	Scene();
	~Scene();
	Entity* GetEntities();
	void AddEntity(Entity entity);

private:
	Entity* entities;
};