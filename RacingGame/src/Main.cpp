#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "include/EventHandler.h"
#include "include/Car.h"

static const sf::Int32 fpsRefreshMs = 1000;
static bool upFlag = false;
static bool downFlag = false;
static bool leftFlag = false;
static bool rightFlag = false;


bool Setup(sf::RenderWindow& window, sf::Text& fpsText, sf::Font& font) {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	window.create(sf::VideoMode(1500, 700), "Racing Game!", sf::Style::Default, settings);

	//never use both setVerticalSyncEnabled and setFramerateLimit at the same time!
	window.setFramerateLimit(60);

	if (!font.loadFromFile("Resources/fonts/MotorolaScreentype.ttf")) {
		std::cout << "Problems opening font file!" << std::endl;
		return false;
	}

	fpsText.setFont(font);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::White);

	return true;
}

int main()
{
	sf::RenderWindow window;
	sf::Text fpsText;
	sf::Font font;

	if (!Setup(window, fpsText, font)) {
		std::cout << "Problems encountered in setup, terminating program!" << std::endl;
		return 0;
	}

	sf::Int32 timeSinceLastFpsLog = fpsRefreshMs;
	Car car = Car(40.0f, 50.0f);

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
				EventHandler::HandleResize(event.size.width, event.size.height);
				break;

			case sf::Event::LostFocus:
				//pause game
				break;

			default:
				break;
			}

		}

		if (upFlag)
			car.Accelerate(dtMillis, true);

		if (downFlag)
			car.Accelerate(dtMillis, false);

		if (leftFlag)
			car.Rotate(dtMillis, true);

		if (rightFlag)
			car.Rotate(dtMillis, false);

		window.clear();
		car.Update(window, dtMillis);
	

		if ((timeSinceLastFpsLog += dtMillis) > fpsRefreshMs) {
			fpsText.setString(std::to_string(static_cast<int>(1000.0f / dtMillis)));
			timeSinceLastFpsLog = 0;
		}
		window.draw(fpsText);
		
		
		window.display();
	}

	return 0;
}