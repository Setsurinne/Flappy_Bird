#pragma once
#include "Timer.h"
class World
{
public:
	World(int FPS, int width, int height);
	~World();

	bool tick();
	int getWidth() const;
	int getHeight() const;

private:
	Timer timer;
	int FPS;
	int screen_width;
	int screen_height;
};

