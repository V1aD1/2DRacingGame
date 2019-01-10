//anything that begins with # is a preprocessor directive,
//so its evaluated by the preprocessor before compiling

//#include literally copies the specified contents into this file
#include <iostream>
#include <thread>

#include "include/ThreadTest.h"

//#define replaces all instances of textToReplace with replacementText
#define textToReplace replacementText

void ThreadTest() {
	std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

	std::thread worker(DoWork);

	std::cin.get();
	FinishWork();

	worker.join();

	std::cout << "Continuing main thread with id = " << std::this_thread::get_id() << std::endl;

	std::cout << "Press ENTER to exit program" << std::endl;
	std::cin.get();
}

int main() {
	ThreadTest();
}