#pragma once
#include "Movable.h"
class Player :
	public Movable
{
public:
	Player(char* playerID, float x, float y, char* image, float initialSpeed);
	~Player();
	virtual void Update(double elapsedTime);
	void OnCollisionEnter(Collidable* collidable) override;
};