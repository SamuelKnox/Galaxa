#ifndef _GAME_H_
#define _GAME_H_

#include "Scene.h"

class Game
{
public:
	Game();
	~Game();
	Scene* GetScenes();

private:
	void SetScene(Scene scene);

	Scene* scenes;
	Scene currentScene;
};

#endif