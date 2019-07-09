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
static const float terrainLen = 50;

//global variables
extern const int screenLen = 1500, screenHeight = 700;

std::vector<Entity*> G_DECORATIVEOBJECTS;
extern std::vector<Entity*> G_STATICOBJECTS;
extern std::vector<Entity*> G_VARIABLEOBJECTS;
extern std::vector<Entity*> G_PARTICLES;
extern std::stack<Entity*> G_FREEPARTICLES;
extern ParticleEmitter G_EMITTER;

WorldSpaceManager worldSpaceManager = WorldSpaceManager();

sf::Vector2f GetTerrainCoords(int x, int y) {
	return sf::Vector2f(x * terrainLen + terrainLen/2, y * terrainLen + terrainLen/2);
}

//a function I'll be using to do performance testing
void PerfTest(sf::RenderWindow& window, EventHandler& eventHandler) {
	Timer("Perf Task");
}

sf::Texture& LoadTexture(std::string path) {
	sf::Texture* textToLoad = new sf::Texture();
	
	textToLoad->setSmooth(true);
	
	if(textToLoad->loadFromFile(path))
		std::cout << "Problems opening texture located at path" << path << "!" << std::endl;

	return *textToLoad;
}

sf::Texture& LoadTexture(std::string path, sf::IntRect intRect) {
	sf::Texture* textToLoad = new sf::Texture();

	textToLoad->setSmooth(true);

	if (!textToLoad->loadFromFile(path, intRect))
		std::cout << "Problems opening texture located at path" << path << "!" << std::endl;

	return *textToLoad;
}

//todo pass an intRect for every texture to read
bool Setup(sf::RenderWindow& window, sf::Font& font, sf::Text& fpsText) {
	Timer("Setup Function");
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(screenLen, screenHeight), "Racing Game!", sf::Style::Default, settings);

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

	sf::Texture car1Text = LoadTexture("Resources/textures/Topdown_vehicle_sprites_pack/Car.png", sf::IntRect(90, 23, 77, 207));
	sf::Texture car2Text = LoadTexture("Resources/textures/Topdown_vehicle_sprites_pack/Mini_truck.png", sf::IntRect(72, 35, 91, 203));
	sf::Texture boxText = LoadTexture("Resources/textures/Props/RTS_Crate.png");
	sf::Texture shrubText = LoadTexture("Resources/textures/Props/shrub.png");

	EventHandler eventHandler = EventHandler();
	
	//important for terrain to be divided into squares
	//important for terrain to be added in a specific order, 
	//so that terrain ranking can be maintained (grass > dirt > road)
	//todo read terrain mappings from a file
	
#pragma region Road

	//top and bottom
	for (int currX = 5, currY = 2; currX < 25; currX++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadTerrain(terrainLen, GetTerrainCoords(currX, currY + 1), sf::Vector2f(1, 1)));

		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadTerrain(terrainLen, GetTerrainCoords(currX, currY + 8), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadTerrain(terrainLen, GetTerrainCoords(currX, currY + 1 + 1 * 8), sf::Vector2f(1, 1)));
	}

	//left and right
	for (int currX = 4, currY = 4; currY < 10; currY++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadTerrain(terrainLen, GetTerrainCoords(currX + 1, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadTerrain(terrainLen, GetTerrainCoords(currX + 1 + 1, currY), sf::Vector2f(1, 1)));

		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadTerrain(terrainLen, GetTerrainCoords(currX + 19, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadTerrain(terrainLen, GetTerrainCoords(currX + 1 + 19, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadTerrain(terrainLen, GetTerrainCoords(currX + 1 + 1 + 19, currY), sf::Vector2f(1, 1)));
	}
#pragma endregion

#pragma region OuterDirt
	//top and bottom
	for (int currX = 5, currY = 1; currX < 25; currX++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX, currY + 11), sf::Vector2f(1, 1)));
	}

	//left and right
	for (int currX = 3, currY = 3; currY < 11; currY++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX + 23, currY), sf::Vector2f(1, 1)));
	}

	for (int currX = 4, currY = 1; currY < 4; currY++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX , currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX + 21, currY), sf::Vector2f(1, 1)));

		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX, currY + 9), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX + 21, currY + 9), sf::Vector2f(1, 1)));
	}
#pragma endregion

#pragma region OutterGrass

	//top and bottom
	for (int currX = 4, currY = 0; currX < 26; currX++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateGrassTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateGrassTerrain(terrainLen, GetTerrainCoords(currX, currY + 13), sf::Vector2f(1, 1)));
	}

	//left and right
	for (int currX = 2, currY = 3; currY < 11; currY++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateGrassTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateGrassTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateGrassTerrain(terrainLen, GetTerrainCoords(currX + 25, currY), sf::Vector2f(1, 1)));
	}
#pragma endregion

#pragma region InnerDirt
	for (int currX = 7, currY = 4; currX < 23; currX++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX, currY + 5), sf::Vector2f(1, 1)));
	}
	
	for (int currX = 7, currY = 5; currY < 9; currY++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		G_STATICOBJECTS.push_back(EntityFactory::CreateDirtTerrain(terrainLen, GetTerrainCoords(currX + 15, currY), sf::Vector2f(1, 1)));
	}
#pragma endregion

#pragma region InnerGrass
	for (int currY = 5; currY < 9; currY++) {
		for (int currX = 8; currX < 22; currX++) {
			G_STATICOBJECTS.push_back(EntityFactory::CreateGrassTerrain(terrainLen, GetTerrainCoords(currX, currY), sf::Vector2f(1, 1)));
		}
	}
#pragma endregion

#pragma region RoadLines

	//top and bottom
	for (int currX = 8; currX < 23; currX++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadLine(20, sf::Vector2f(currX * terrainLen, 3 * terrainLen), 0));
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadLine(20, sf::Vector2f(currX * terrainLen, 11 * terrainLen), 0));

	}

	//left and right
	for (int currY = 5; currY < 10; currY++) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadLine(20, sf::Vector2f(5.5 * terrainLen, currY * terrainLen), 90));
		G_STATICOBJECTS.push_back(EntityFactory::CreateRoadLine(20, sf::Vector2f(24.5 * terrainLen, currY * terrainLen), 90));
	}
#pragma endregion

#pragma region Barriers

	//top left corner
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(175, 125), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(125, 125), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(175, 75), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(125, 75), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(175, 25), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(125, 25), 0, sf::Vector2f(0.1, 0.1), boxText));

	//top right
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(1375, 125), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(1325, 125), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(1375, 75), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(1325, 75), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(1375, 25), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(1325, 25), 0, sf::Vector2f(0.1, 0.1), boxText));
	
	//bottom left
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(175, 675), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(125, 675), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(175, 625), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(125, 625), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(175, 575), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(125, 575), 0, sf::Vector2f(0.1, 0.1), boxText));

	//bottom right
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(1375, 670), 0, sf::Vector2f(0.1, 0.1), boxText));

	/*G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(125, 125), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(175, 75), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(125, 75), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(175, 25), 0, sf::Vector2f(0.1, 0.1), boxText));
	G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(125, 25), 0, sf::Vector2f(0.1, 0.1), boxText));*/

	//centre
	for (int currX = 550; currX < 1000; currX += 50) {
		G_STATICOBJECTS.push_back(EntityFactory::CreateStaticCollisionObject(sf::Vector2f(currX, 350), 0, sf::Vector2f(0.1, 0.1), boxText));
	}


#pragma endregion

#pragma region Decorations
	G_DECORATIVEOBJECTS.push_back(EntityFactory::CreateDecorativeObject(sf::Vector2f(480, 340), 0, sf::Vector2f(0.5, 0.5), shrubText));
	G_DECORATIVEOBJECTS.push_back(EntityFactory::CreateDecorativeObject(sf::Vector2f(1020, 340), 0, sf::Vector2f(0.5, 0.5), shrubText));
#pragma endregion

	auto player1 = EntityFactory::CreatePlayer1(sf::Vector2f(6 * terrainLen, 2.5 * terrainLen), 90.0f, car1Text);	
	auto player2 = EntityFactory::CreatePlayer2(sf::Vector2f(6 * terrainLen, 3.5 * terrainLen), 90.0f, car2Text);
	auto emitter = ParticleEmitter();

	G_VARIABLEOBJECTS.push_back(player1);
	G_VARIABLEOBJECTS.push_back(player2);

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

		for (auto decorativeObject : G_DECORATIVEOBJECTS) {
			decorativeObject->Update(window, dtMillis, eventHandler);
		}

		if (eventHandler.qFlag)
		{
			emitter.EmitCone(sf::Vector2f(200, 400), player1->m_physics->GetForwardDir(), 0.2f, 0.3f, 1.25f, 1.0f, -1.0f, 60, 1, 90);
			//emitter.EmitCircle(sf::Vector2f(200, 400), 0.2f, 0.3f, 1.25f, 1.0f, -1.0f, 1, 90);
		}

		//worldSpaceManager.DBG_Draw(window);

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