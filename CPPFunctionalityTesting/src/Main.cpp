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

int main() {

	std::cout << "Press ENTER to exit program" << std::endl;
	std::cin.get();
}