#include "PhoneHome.h"

PhoneHome::PhoneHome()
{
}


PhoneHome::~PhoneHome()
{
}

void PhoneHome::PlayGame() {
	//Create Game
	Game* game = new Game();
	Scene* scene = new Scene();
	game->SetScene(*scene);

	//Create Player
	Player* player = new Player("Player", 50, 50, "filepath/player.png", 5);
	scene->AddEntity(player);

	//Create Hole
	Hole* hole = new Hole("Hole", 10, 50, "filepath/hole.png");
	scene->AddEntity(hole);

	player->SetVelocity(-1, 0);
	//OnCollisionEnter in the player class should trigger and the hole
}