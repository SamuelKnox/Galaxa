#include "Scene.h"

#pragma once
class Game
{
public:
	Game();
	~Game();
	Scene* GetScenes();
	void StartGame();
	void SetScene(Scene scene);

private:
	Scene* scenes;
	Scene currentScene;
	double previousTime;
};

