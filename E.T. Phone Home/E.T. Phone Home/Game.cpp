#include "Game.h"
#include "Scene.h"



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