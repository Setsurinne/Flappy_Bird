#pragma once
#include <chrono>

/// <summary>
/// Timer is a class to help user get time tick in the game
/// </summary>
class Timer
{
public:
	Timer();

	/// <summary>
	/// Synchronizing last called time to now
	/// </summary>
	void startTick();

	/// <summary>
	/// Check if one fame has passed compared to last called time
	/// </summary>
	/// <param name="frame_per_sec"> The number of frame required per sec </param>
	/// <returns> True iff one frame based on given FPS has passed </returns>
	bool oneFramePassed(int frame_per_sec);

private:
	std::chrono::steady_clock::time_point last_call_time;
};

