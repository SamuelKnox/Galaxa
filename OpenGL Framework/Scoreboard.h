#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include "baseTypes.h"
#include "gamedefs.h"
#include "Sprite.h"

class Scoreboard
{
public:
	Scoreboard();
	~Scoreboard();
	int32_t score;
	void Render();

private:
	Sprite* lines[NUM_LINES] = { nullptr };
};

#endif