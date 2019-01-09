#include "Log.h"
#include <iostream>


void Log::SetLevel(int level) {
	logLevel = level;

}

void Log::Error(const char* message) {
	std::cout << "[ERROR]: " << message << std::endl;
}

void Log::Warn(const char* message) {
	std::cout << "[WARNING]: " << message << std::endl;
}

void Log::Info(const char* message) {
	std::cout << "[INFO]: " << message << std::endl;
}