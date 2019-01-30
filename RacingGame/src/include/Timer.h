#pragma once
#include <chrono>
#include <string>

class Timer
{
public:
	Timer();
	Timer(const std::string& action);

	~Timer();

private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	std::string actionName;
};

