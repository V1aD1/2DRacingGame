#include <iostream>
#include <vector>

#include "include/FunctionPointerTest.h"

void HelloWorldWithParam(int a) {
	std::cout << "Hello World! Vlaue: " << a << std::endl;
}

void HelloWorld() {
	std::cout << "Hello world!"<< std::endl;
}

void ForEach(const std::vector<int>& values, void(*func)(int)) {
	for (int value : values)
		func(value);
}

void PrintValue(int a) {
	std::cout << "Value: " << a << std::endl;
}

void FunctionPointerTest()
{
	//usually use auto instead of specifying the actual variable type, so:
	//auto function = HelloWorld;
	void(*helloWorldNoParams)() = &HelloWorld;

	auto helloWorldWithParams = HelloWorldWithParam;

	//this calls the function
	helloWorldNoParams();

	//this calls the function with parameters
	helloWorldWithParams(5);

	std::vector<int> values = { 1,2,3,4 };

	//passing in function pointers as parameters to a function
	ForEach(values, PrintValue);

	//this also works
	ForEach(values, [](int value) {std::cout << "Value: " << value << std::endl; });

}

