#include <iostream>

#include "include/EventHandler.h"



EventHandler::EventHandler()
{
}


void EventHandler::HandleResize(int width, int height) {
	//std::cout << "New width: " << width << std::endl;
	//std::cout << "New height: " << height << std::endl;
}

void EventHandler::HandleEvent(sf::RenderWindow& window, sf::Event& event) {
	switch (event.type) {

	case sf::Event::Closed:
		window.close();
		break;

	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			window.close();
			break;
		case sf::Keyboard::Up:
			upFlag = true;
			break;
		case sf::Keyboard::Down:
			downFlag = true;
			break;
		case sf::Keyboard::Left:
			leftFlag = true;
			break;
		case sf::Keyboard::Right:
			rightFlag = true;
			break;
		case sf::Keyboard::Space:
			spaceFlag = true;
			break;

		case sf::Keyboard::W:
			wFlag = true;
			break;
		case sf::Keyboard::S:
			sFlag = true;
			break;
		case sf::Keyboard::A:
			aFlag = true;
			break;
		case sf::Keyboard::D:
			dFlag = true;
			break;
		}
		break;

	case sf::Event::KeyReleased:
		switch (event.key.code) {
		case sf::Keyboard::Up:
			upFlag = false;
			break;
		case sf::Keyboard::Down:
			downFlag = false;
			break;
		case sf::Keyboard::Left:
			leftFlag = false;
			break;
		case sf::Keyboard::Right:
			rightFlag = false;
			break;
		case sf::Keyboard::Space:
			spaceFlag = false;
			break;

		case sf::Keyboard::W:
			wFlag = false;
			break;
		case sf::Keyboard::S:
			sFlag = false;
			break;
		case sf::Keyboard::A:
			aFlag = false;
			break;
		case sf::Keyboard::D:
			dFlag = false;
			break;
		}
		break;

	case sf::Event::Resized:
		HandleResize(event.size.width, event.size.height);
		break;

	case sf::Event::LostFocus:
		//todo pause game
		break;

	default:
		break;
	}
}

EventHandler::~EventHandler()
{
}
