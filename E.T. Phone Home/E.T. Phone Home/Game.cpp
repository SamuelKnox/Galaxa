#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

Scene* Game::GetScenes() {
	return scenes;
}

void Game::SetScene(Scene scene) {
	currentScene = scene;
}

void Game::StartGame() {
	previousTime = XtraLayer.GetCurrentTime();
	while (true) {
		double currentTime = XtraLayer.GetCurrentTime();
		double elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		for each (Entity entity in currentScene.GetEntities())
		{
			entity.Update(elapsedTime);
			entity.Draw();
		}
	}
}