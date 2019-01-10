#include <iostream>
#include <thread>
#include "include/ThreadTest.h"

static bool s_Finished = false;

void DoWork() {
	using namespace std::literals::chrono_literals;

	std::cout << "Started thread with id = " << std::this_thread::get_id() << std::endl;

	while (!s_Finished) {
		std::cout << "Working..." << std::endl;
		std::this_thread::sleep_for(1s);
	}
}

void FinishWork() {
	s_Finished = true;
}