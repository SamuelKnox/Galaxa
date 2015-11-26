#include "Scene.h"

Scene::Scene()
{
	entitiesHead = nullptr;
	entitiesTail = nullptr;
}


Scene::~Scene()
{
	entityNodeT *node = entitiesHead;

	while (node != nullptr)
	{
		entityNodeT *next = node->next;
		delete node;
		node = next;
	}

	entitiesHead = nullptr;
	entitiesTail = nullptr;
}

//Entity* Scene::GetEntities() {
//	return entities;
//}

void Scene::AddEntity(Entity newEntity) {
	entityNodeT *newNode = new entityNodeT();
	newNode->entity = newEntity;
	newNode->next = nullptr;

	if (entitiesHead == nullptr)
	{
		entitiesHead = newNode;
	}

	if (entitiesTail != nullptr)
	{
		entitiesTail->next = newNode;
	}

	entitiesTail = newNode;
}