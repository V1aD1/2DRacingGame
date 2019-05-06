#include <iostream>

#include "EventHandler.h"



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
			upFlagP1 = true;
			break;
		case sf::Keyboard::Down:
			downFlagP1 = true;
			break;
		case sf::Keyboard::Left:
			leftFlagP1 = true;
			break;
		case sf::Keyboard::Right:
			rightFlagP1 = true;
			break;
		case sf::Keyboard::Space:
			brakeFlagP1 = true;
			break;

		case sf::Keyboard::Numpad8:
			upFlagP2 = true;
			break;
		case sf::Keyboard::Numpad5:
			downFlagP2 = true;
			break;
		case sf::Keyboard::Numpad4:
			leftFlagP2 = true;
			break;
		case sf::Keyboard::Numpad6:
			rightFlagP2 = true;
			break;
		case sf::Keyboard::Numpad0:
			brakeFlagP2 = true;
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

		case sf::Keyboard::T:
			tFlag = true;
			break;
		case sf::Keyboard::G:
			gFlag = true;
			break;
		case sf::Keyboard::F:
			fFlag = true;
			break;
		case sf::Keyboard::H:
			hFlag = true;
			break;
		case sf::Keyboard::Q:
			qFlag = true;
			break;
		}
		break;

	case sf::Event::KeyReleased:
		switch (event.key.code) {
		case sf::Keyboard::Up:
			upFlagP1 = false;
			break;
		case sf::Keyboard::Down:
			downFlagP1 = false;
			break;
		case sf::Keyboard::Left:
			leftFlagP1 = false;
			break;
		case sf::Keyboard::Right:
			rightFlagP1 = false;
			break;
		case sf::Keyboard::Space:
			brakeFlagP1 = false;
			break;

		case sf::Keyboard::Numpad8:
			upFlagP2 = false;
			break;
		case sf::Keyboard::Numpad5:
			downFlagP2 = false;
			break;
		case sf::Keyboard::Numpad4:
			leftFlagP2 = false;
			break;
		case sf::Keyboard::Numpad6:
			rightFlagP2 = false;
			break;
		case sf::Keyboard::Numpad0:
			brakeFlagP2 = false;
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

		case sf::Keyboard::T:
			tFlag = false;
			break;
		case sf::Keyboard::G:
			gFlag = false;
			break;
		case sf::Keyboard::F:
			fFlag = false;
			break;
		case sf::Keyboard::H:
			hFlag = false;
			break;
		case sf::Keyboard::Q:
			qFlag = false;
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
