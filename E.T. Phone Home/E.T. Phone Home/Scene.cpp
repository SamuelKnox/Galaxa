#include "Scene.h"
#include "Entity.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

Entity* Scene::GetEntities() {
	return entities;
}

void Scene::AddEntity(Entity entity) {
	//entities.Add(entity);
}