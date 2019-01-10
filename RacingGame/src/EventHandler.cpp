#include <iostream>

#include "EventHandler.h"



EventHandler::EventHandler()
{
}


void EventHandler::HandleResize(int width, int height) {
	std::cout << "New width: " << width << std::endl;
	std::cout << "New height: " << height << std::endl;
}

EventHandler::~EventHandler()
{
}
