#pragma once
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

