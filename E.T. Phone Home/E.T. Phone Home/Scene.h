#ifndef _SCENE_H_
#define _SCENE_H_

#include "Entity.h"

class Scene
{

public:

	struct entityNode
	{
		Entity entity;
		struct entityNode *next;
	} *entitiesHead, *entitiesTail;
	typedef struct entityNode entityNodeT;

	Scene();
	~Scene();

	//Entity* GetEntities();
	void AddEntity(Entity entity);

};

#endif