//anything that begins with # is a preprocessor directive,
//so its evaluated by the preprocessor before compiling

//#include literally copies the specified contents into this file
#include <iostream>
#include "Log.cpp"

//#define replaces all instances of textToReplace with replacementText
#define textToReplace replacementText

#define 

int main() {
	
	Log log;

	log.SetLevel(1);
	log.Warn("Warning");
	
	std::cin.get();
}