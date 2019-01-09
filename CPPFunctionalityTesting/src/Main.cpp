//anything that begins with # is a preprocessor directive,
//so its evaluated by the preprocessor before compiling
#include <iostream>
#include "Log.h"

int main() {

	int a = 8;
	a++;
	const char * string = "Hello";

	for (int i = 0; i < 5; i++) {
		char c = string[i];
		std::cout << c << std::endl;
	}

	Log("Logging...");
	std::cin.get();
}