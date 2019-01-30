#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "include/EventHandler.h"
#include "include/Car.h"
#include "include/Square.h"
#include "include/Timer.h"

static const sf::Int32 fpsRefreshMs = 1000;
static const int screenLen = 1500, screenHeight = 700;


bool Setup(sf::RenderWindow& window, sf::Font& font, sf::Text& fpsText) {
	Timer("Setup Function ");
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(screenLen, screenHeight), "Racing Game!", sf::Style::Default, settings);

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

	EventHandler eventHandler;


	if (!Setup(window, font, fpsText)) {
		std::cout << "Problems encountered in setup, terminating program!" << std::endl;
		return 0;
	}

	eventHandler = EventHandler();

	sf::Int32 timeSinceLastFpsLog = fpsRefreshMs;
	Car car = Car(sf::Vector2f(40.0f, 50.0f));
	Square square = Square(250, sf::Vector2f(screenLen / 2, screenHeight / 2), 45.0f);


	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Int32 dtMillis = (clock.restart()).asMilliseconds();
		sf::Event event;

		//pollEvent() or waitEvent() MUST be called in the same thread that created the window!!
		while (window.pollEvent(event))
		{
			eventHandler.HandleEvent(window, event);
		}

		if (eventHandler.upFlag)
			car.Accelerate(dtMillis, true);

		if (eventHandler.downFlag)
			car.Accelerate(dtMillis, false);

		if (eventHandler.leftFlag)
			car.Rotate(dtMillis, true);

		if (eventHandler.rightFlag)
			car.Rotate(dtMillis, false);

		if (eventHandler.spaceFlag)
			car.Brake(dtMillis);

		//debug commands
		if (eventHandler.wFlag)
			car.DBG_Slide(sf::Vector2f(0.0f, -1.0f), dtMillis);

		if (eventHandler.sFlag)
			car.DBG_Slide(sf::Vector2f(0.0f, 1.0f), dtMillis);

		if (eventHandler.aFlag)
			car.DBG_Slide(sf::Vector2f(-1.0f, 0.0f), dtMillis);

		if (eventHandler.dFlag)
			car.DBG_Slide(sf::Vector2f(1.0f, 0.0f), dtMillis);

		window.clear();
		car.Update(window, dtMillis);
		square.Update(window, dtMillis);

		if ((timeSinceLastFpsLog += dtMillis) > fpsRefreshMs) {
			fpsText.setString(std::to_string(static_cast<int>(1000.0f / dtMillis)));
			timeSinceLastFpsLog = 0;
		}
		window.draw(fpsText);


		window.display();
	}

	return 0;
}