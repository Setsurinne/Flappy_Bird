#include "Timer.h"
#include <iostream>

Timer::Timer() {
	this->last_call_time = std::chrono::steady_clock::now();
}

void Timer::startTick() {
	this->last_call_time = std::chrono::steady_clock::now();
}

bool Timer::oneFramePassed(int frame_per_sec) {
	//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_call_time).count() << std::endl;
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_call_time).count() >= 1000 / frame_per_sec){
		startTick();
		return true;
	}
	return false;
}