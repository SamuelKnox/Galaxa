#include "Player.h"



Player::Player(char* playerID, float x, float y, char* image, float initialSpeed) : Movable(playerID, x, y, image, initialSpeed)
{
}


Player::~Player()
{
}

void Player::Update(double elapsedTime) {
	//Update Velocity based on input
	Movable::Update(elapsedTime);
	double horizontalInput = XtraLayer.GetHorizontalInput();
	double verticalInput = XtraLayer.GetVerticalInput();
	SetVelocity(horizontalInput, verticalInput);
}

void Player::OnCollisionEnter(Collidable* collidable) {

}