#pragma once
#include "Collidable.h"
class Hole :
	public Collidable
{
public:
	Hole(char* holeID, float x, float y, char* image);
	~Hole();
};

