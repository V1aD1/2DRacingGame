#include <iostream>

#include "include/EventHandler.h"



EventHandler::EventHandler()
{
}


void EventHandler::HandleResize(int width, int height) {
	std::cout << "New width: " << width << std::endl;
	std::cout << "New height: " << height << std::endl;
}

void EventHandler::HandleEvent(sf::RenderWindow& window, sf::Event& event) {
	switch (event.type) {

	case sf::Event::Closed:
		window.close();
		break;

	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Escape)
			window.close();

		if (event.key.code == sf::Keyboard::Up)
			upFlag = true;

		if (event.key.code == sf::Keyboard::Down)
			downFlag = true;

		if (event.key.code == sf::Keyboard::Left)
			leftFlag = true;

		if (event.key.code == sf::Keyboard::Right)
			rightFlag = true;

		break;

	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::Up)
			upFlag = false;

		if (event.key.code == sf::Keyboard::Down)
			downFlag = false;

		if (event.key.code == sf::Keyboard::Left)
			leftFlag = false;

		if (event.key.code == sf::Keyboard::Right)
			rightFlag = false;

	case sf::Event::Resized:
		HandleResize(event.size.width, event.size.height);
		break;

	case sf::Event::LostFocus:
		//pause game
		break;

	default:
		break;
	}
}

EventHandler::~EventHandler()
{
}
