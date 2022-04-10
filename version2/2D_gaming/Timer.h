#pragma once
#include <chrono>

class Timer
{
public:
	Timer();

	void startTick();
	bool oneFramePassed(int frame_per_sec);
private:
	std::chrono::steady_clock::time_point last_call_time;
};

