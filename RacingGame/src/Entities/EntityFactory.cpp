#include "EntityFactory.h"
#include "Entity.h"

#include "Static/SquareGraphicsComponent.h"
#include "Car/CarGraphicsComponent.h"
#include "Particle/ParticleGraphicsComponent.h"

#include "Car/CarPhysicsComponent.h"
#include "Particle/ParticlePhysicsComponent.h"

#include "Car/InputComponentP1.h"
#include "Car/InputComponentP2.h"

#include "../Components/StaticCollisionComponent.h"
#include "../Components/VariableCollisionComponent.h"

#include "../Other/MathCommon.h"

const float EntityFactory::c_car_length = 40.0f;
const float EntityFactory::c_car_height = 10.0f;


Entity* EntityFactory::CreateSquare(float sideLen, sf::Vector2f pos, float rotDeg) {
	float halfSideLen = sideLen / 2;

	sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape->setOrigin(halfSideLen, halfSideLen);
	shape->setFillColor(sf::Color::Red);

	std::vector<sf::Vector2f> localCorners;
	std::vector<sf::Vector2f> worldCorners;


	localCorners.push_back(sf::Vector2f(-halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, halfSideLen));
	localCorners.push_back(sf::Vector2f(-halfSideLen, halfSideLen));

	auto graphics = new SquareGraphicsComponent(shape);
	auto collision = new StaticCollisionComponent(pos, MathCommon::DegreesToRadians(rotDeg), localCorners);

	return new Entity(pos, rotDeg, nullptr, nullptr, graphics, collision);
}

Entity * EntityFactory::CreatePlayer1(sf::Vector2f pos)
{
	return CreateCar(pos, sf::Color::Blue, new InputComponentP1());
}

Entity * EntityFactory::CreatePlayer2(sf::Vector2f pos)
{
	return CreateCar(pos, sf::Color::Yellow, new InputComponentP2());
}

Entity * EntityFactory::CreateCar(sf::Vector2f startPos, sf::Color color, InputComponent* inputCom)
{
	auto size = sf::Vector2f(c_car_length, c_car_height);

	//create shape for graphics component
	sf::RectangleShape* shape = new sf::RectangleShape(size);
	shape->setFillColor(color);
	shape->setOutlineThickness(1.0f);
	shape->setOutlineColor(sf::Color(250, 150, 100));
	shape->setOrigin(size.x / 2.0f, size.y / 2.0f);
	shape->setPosition(0.0f, 0.0f);


	//create corners for physics component
	std::vector<sf::Vector2f> corners = std::vector<sf::Vector2f>();
	corners.push_back(sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f));
	corners.push_back(sf::Vector2f(size.x / 2.0f, -size.y / 2.0f));
	corners.push_back(sf::Vector2f(size.x / 2.0f, size.y / 2.0f));
	corners.push_back(sf::Vector2f(-size.x / 2.0f, size.y / 2.0f));

	auto physics = new CarPhysicsComponent(startPos, MathCommon::DegreesToRadians(0.0f), corners);
	auto graphics = new CarGraphicsComponent(shape);
	auto collision = new VariableCollisionComponent(startPos, 0.0f, corners);

	return new Entity(startPos, 0.0f, inputCom, physics, graphics, collision);
}

Entity * EntityFactory::CreateParticle(float alphaChangeRate)
{
	return new Entity(sf::Vector2f(50, 500), 0, nullptr, new ParticlePhysicsComponent(), new ParticleGraphicsComponent(alphaChangeRate), nullptr);
}





