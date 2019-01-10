#include <SFML/Graphics.hpp>

#include "EventHandler.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Racing Game!", sf::Style::Default);
	
	//never use both setVerticalSyncEnabled and setFramerateLimit at the same time!
	window.setFramerateLimit(60);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Int32 dtMillis = (clock.restart()).asMilliseconds();
		sf::Event event;

		//pollEvent() or waitEvent() MUST be called in the same thread that created the window!!
		while (window.pollEvent(event))
		{
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;

			case sf::Event::Resized:
				EventHandler::HandleResize(event.size.width, event.size.height);
				break;

			case sf::Event::LostFocus:
				//pause game
				break;

			default:
				break;
			}

		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}