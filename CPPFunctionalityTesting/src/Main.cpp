//anything that begins with # is a preprocessor directive,
//so its evaluated by the preprocessor before compiling

//#include literally copies the specified contents into this file
#include <iostream>
#include <thread>
#include <array>
#include <chrono>
#include <thread>

#include "include/ThreadTest.h"
#include "include/FunctionPointerTest.h"

//this is a macro, mostly used for debug purposes
//#define replaces all instances of textToReplace with replacementText,
//in the preprocessing stage
#define textToReplace replacementText

//macro example
#define LOG(x) std::cout << x << std::endl;

void ThreadTest() {
	std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

	std::thread worker(DoWork);

	std::cin.get();
	FinishWork();

	//waits for thread to finish before advancing
	worker.join();

	std::cout << "Continuing main thread with id = " << std::this_thread::get_id() << std::endl;
}

//templates generate code according to the specified template
template <typename T>
void TemplatePrint(T value) {
	std::cout << value << std::endl;
}

template <typename T, int N>
class TemplateArray {
private:
	T m_Array[N];

public:
	int GetSize() const { return N; }

};

void ArrayTest() {
	//similar to c-style arrays,
	//but has more properties, namely size(),
	//and has optional bounds checking in DEBUG BUILD
	//at no performance cost
	std::array<int, 5> data;
	int size = data.size();
}

void HowToTime() {

	using namespace std::literals::chrono_literals;

	auto start = std::chrono::high_resolution_clock::now();

	std::this_thread::sleep_for(1s);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;

	std::cout << "Seconds passed: " << duration.count() << std::endl;
}

int main() {
	HowToTime();
	std::cout << "Press ENTER to exit program" << std::endl;
	std::cin.get();
}