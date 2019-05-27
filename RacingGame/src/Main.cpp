/////////////////////// MOTIVATIONAL LINKS ///////////////////////////////////////////////
//
//Motivation for lack of exceptions: https://www.reddit.com/r/programming/comments/6s2izd/johnathan_blow_on_criticizing_engineering_and_c/
//
//
//////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Other/EventHandler.h"
#include "Other/Timer.h"
#include "Entities/Entity.h"
#include "Entities/EntityFactory.h"
#include "Other/WorldSpaceManager.h"
#include "Entities/Particle/ParticleEmitter.h"

static const sf::Int32 fpsRefreshMs = 500;

//global variables
extern const int screenLen = 1500, screenHeight = 700;

extern std::vector<Entity*> G_STATICOBJECTS;
extern std::vector<Entity*> G_VARIABLEOBJECTS;
extern std::vector<Entity*> G_PARTICLES;
extern std::stack<Entity*> G_FREEPARTICLES;
extern ParticleEmitter G_EMITTER;

WorldSpaceManager worldSpaceManager = WorldSpaceManager();

//a function I'll be using to do performance testing
void PerfTest(sf::RenderWindow& window, EventHandler& eventHandler) {
	Timer("Perf Task");
}

bool Setup(sf::RenderWindow& window, sf::Font& font, sf::Text& fpsText) {
	Timer("Setup Function");
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(screenLen, screenHeight), "Racing Game!", sf::Style::Default, settings);

	//todo frame rate affects particles...

	//never use both setVerticalSyncEnabled and setFramerateLimit at the same time!
	//window.setFramerateLimit(200);

	if (!font.loadFromFile("Resources/fonts/MotorolaScreentype.ttf")) {
		std::cout << "Problems opening font file!" << std::endl;
		return false;
	}

	fpsText.setFont(font);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::White);

	G_EMITTER.Init();

	return true;
}

int main()
{
	sf::RenderWindow window;
	sf::Text fpsText;
	sf::Font font;
	sf::Clock clock;
	sf::Int32 timeSinceLastFpsLog = fpsRefreshMs;

	//EntityFactory entityFactory = EntityFactory();
	EventHandler eventHandler = EventHandler();
	auto player1 = EntityFactory::CreatePlayer1(sf::Vector2f(40.0f, 50.0f));
	auto player2 = EntityFactory::CreatePlayer2(sf::Vector2f(40.0f, 90.0f));
	auto square = EntityFactory::CreateSquare(250, sf::Vector2f(screenLen / 2, screenHeight / 2), 123.0f);
	auto emitter = ParticleEmitter();


	G_VARIABLEOBJECTS.push_back(player1);
	G_VARIABLEOBJECTS.push_back(player2);
	G_STATICOBJECTS.push_back(square);


	/*for (int j = 1; j < 50; j++) {
		for (int i = 1; i < 30; i++) {
			auto square1 = entityFactory.CreateSquare(10, sf::Vector2f(20 * j + 50, 20 * i + 50), 0.0f);
			G_STATICOBJECTS.push_back(square1);
		}
	}*/

	if (!Setup(window, font, fpsText)) {
		std::cout << "Problems encountered in setup, terminating program!" << std::endl;
		return 0;
	}

	worldSpaceManager.UpdateAllEntitiesInCollSpace();

	PerfTest(window, eventHandler);

	while (window.isOpen())
	{
		sf::Time timePassed = clock.restart();
		sf::Int64 dtMicros = timePassed.asMicroseconds();
		float dtMillis = dtMicros / 1000.0f;
		sf::Event event;

		//pollEvent() or waitEvent() MUST be called in the same thread that created the window!!
		while (window.pollEvent(event))
		{
			eventHandler.HandleEvent(window, event);
		}

		window.clear();

		worldSpaceManager.UpdateVariableEntitiesInCollSpace();

		//update static objects before variable objects
		for (auto staticObject : G_STATICOBJECTS) {
			staticObject->Update(window, dtMillis, eventHandler);
		}

		for (auto particle : G_PARTICLES) {
			if (particle->m_graphics->GetShape()->getFillColor().a > 0) {
				particle->Update(window, dtMillis, eventHandler);
			}
		}

		for (auto variableObject : G_VARIABLEOBJECTS) {
			variableObject->Update(window, dtMillis, eventHandler);
		}

		if (eventHandler.qFlag)
		{
			emitter.EmitCone(sf::Vector2f(200, 400), player1->m_physics->GetForwardDir(), 0.2f, 0.3f, 1.25f, -200.0f, -1.0f, 60, 1, 90);
		}

		worldSpaceManager.DBG_Draw(window);

		if ((timeSinceLastFpsLog += dtMillis) > fpsRefreshMs) {
			fpsText.setString(std::to_string(static_cast<int>(1000000.0f / dtMicros)));
			timeSinceLastFpsLog = 0;
		}

		window.draw(fpsText);
		window.display();

		worldSpaceManager.ClearVariableEntities();
	}

	return 0;
}