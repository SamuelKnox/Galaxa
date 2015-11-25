#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

Entity* Scene::GetEntities() {
	return entities;
}

void Scene::AddEntity(Entity* entity) {
	entities.Add(entity);
}

void Scene::UpdateEntities() {

}

void Scene::DrawSprites() {

}