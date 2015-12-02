#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include "jsy/types.h"
#include "gamedefs.h"
#include "Sprite.h"

class Scoreboard
{
public:
	Scoreboard();
	~Scoreboard();
	int32_t score;
	void Render();
	void Reset();

private:
	Sprite* lines[NUM_LINES] = { nullptr };
	Sprite* label;
};

#endif