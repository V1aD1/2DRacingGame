#include <iostream>

#include "include/EventHandler.h"



EventHandler::EventHandler()
{
}


void EventHandler::HandleResize(int width, int height) {
	std::cout << "New width: " << width << std::endl;
	std::cout << "New height: " << height << std::endl;
}

void EventHandler::HandleInput() {

}

EventHandler::~EventHandler()
{
}
