#pragma once
#include "Timer.h"

/// <summary>
/// A World is designed to track global variables in one game
/// Including FPS, Window size, and Timer ...
/// </summary>
class World
{
public:
	World(int FPS, int width, int height);
	~World();

	/// <summary>
	/// Check if one tick has passed since the last call
	/// </summary>
	/// <returns> True iff one tick has passed based on game FPS </returns>
	bool tick();

	/// <summary>
	/// Get the game window height
	/// </summary>
	/// <returns> The height of the window </returns>
	int getWidth() const;

	/// <summary>
	/// Get the game window width
	/// </summary>
	/// <returns> The width of the window </returns>
	int getHeight() const;

private:
	Timer timer;
	int FPS;
	int screen_width;
	int screen_height;
};

