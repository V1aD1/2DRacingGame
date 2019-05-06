#include <chrono>
#include <iostream>
#include <string>

#include "Timer.h"

Timer::Timer()
{
	start = std::chrono::high_resolution_clock::now();
	actionName = "";
}


Timer::Timer(const std::string& action) {
	actionName = action;
	start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;

	std::cout << actionName << "Action took: " << duration.count() * 1000.0f << " ms" << std::endl;
}
