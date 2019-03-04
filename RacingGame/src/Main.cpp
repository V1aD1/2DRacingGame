#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "include/EventHandler.h"
#include "include/Timer.h"
#include "include/Entity.h"
#include "include/EntityFactory.h"
#include "include/WorldSpaceManager.h"

static const sf::Int32 fpsRefreshMs = 500;

//global variables
extern const int screenLen = 1500, screenHeight = 700;
std::vector<Entity*> G_STATICOBJECTS;
std::vector<Entity*> G_VARIABLEOBJECTS;
WorldSpaceManager worldSpaceManager = WorldSpaceManager();

bool Setup(sf::RenderWindow& window, sf::Font& font, sf::Text& fpsText) {
	Timer("Setup Function ");
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(screenLen, screenHeight), "Racing Game!", sf::Style::Default, settings);

	//never use both setVerticalSyncEnabled and setFramerateLimit at the same time!
	//window.setFramerateLimit(60);

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
	sf::Clock clock;
	sf::Int32 timeSinceLastFpsLog = fpsRefreshMs;

	EntityFactory entityFactory = EntityFactory();
	EventHandler eventHandler = EventHandler();
	auto car = entityFactory.CreateCar(sf::Vector2f(40.0f, 50.0f));
	auto square = entityFactory.CreateSquare(250, sf::Vector2f(screenLen / 2, screenHeight / 2), 123.0f);

	G_VARIABLEOBJECTS.push_back(car);
	G_STATICOBJECTS.push_back(square);

	if (!Setup(window, font, fpsText)) {
		std::cout << "Problems encountered in setup, terminating program!" << std::endl;
		return 0;
	}

	while (window.isOpen())
	{
		sf::Time timePassed = clock.restart();
		sf::Int32 dtMicros = timePassed.asMicroseconds();
		float dtMillis = dtMicros / 1000.0f;
		sf::Event event;

		//pollEvent() or waitEvent() MUST be called in the same thread that created the window!!
		while (window.pollEvent(event))
		{
			eventHandler.HandleEvent(window, event);
		}

		window.clear();
		
		worldSpaceManager.PopulateCollisionSpace();

		//update static objects before variable objects
		for (auto staticObjects : G_STATICOBJECTS) {
			staticObjects->Update(window, dtMillis, eventHandler);
		}

		for (auto variableObjects : G_VARIABLEOBJECTS) {
			variableObjects->Update(window, dtMillis, eventHandler);
		}

		worldSpaceManager.DBG_Draw(window);

		if ((timeSinceLastFpsLog += dtMillis) > fpsRefreshMs) {
			fpsText.setString(std::to_string(static_cast<int>(1000000.0f / dtMicros)));
			timeSinceLastFpsLog = 0;
		}

		window.draw(fpsText);
		window.display();
		
		//todo this destorys my performance!!!!
		worldSpaceManager.ClearWorldSpace();
	}

	return 0;
}