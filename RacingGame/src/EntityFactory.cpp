#include "include/EntityFactory.h"
#include "include/Entity.h"
#include "include/SquareGraphicsComponent.h"
#include "include/MathCommon.h"
#include "include/CarGraphicsComponent.h"
#include "include/CarPhysicsComponent.h"

const float EntityFactory::c_car_length = 40.0f;
const float EntityFactory::c_car_height = 10.0f;

EntityFactory::EntityFactory()
{
}


EntityFactory::~EntityFactory()
{
}

Entity* EntityFactory::CreateSquare(float sideLen, sf::Vector2f pos, float rotDeg) {
	float halfSideLen = sideLen / 2;

	sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape->setOrigin(halfSideLen, halfSideLen);
	shape->setFillColor(sf::Color::Red);

	std::array<sf::Vector2f, 4> localCorners;
	std::array<sf::Vector2f, 4> worldCorners;


	localCorners[0] = sf::Vector2f(-halfSideLen, -halfSideLen);
	localCorners[1] = sf::Vector2f(halfSideLen, -halfSideLen);
	localCorners[2] = sf::Vector2f(halfSideLen, halfSideLen);
	localCorners[3] = sf::Vector2f(-halfSideLen, halfSideLen);

	auto graphics = new SquareGraphicsComponent(shape);
	auto collision = new CollisionComponent(pos, MathCommon::DegreesToRadians(rotDeg), localCorners);

	return new Entity(pos, rotDeg, nullptr, nullptr, graphics, collision);
}

Entity * EntityFactory::CreateCar(sf::Vector2f startPos)
{
	auto size = sf::Vector2f(c_car_length, c_car_height);

	//create shape for graphics component
	sf::RectangleShape* shape = new sf::RectangleShape(size);
	shape->setFillColor(sf::Color::Blue);
	shape->setOutlineThickness(1.0f);
	shape->setOutlineColor(sf::Color(250, 150, 100));
	shape->setOrigin(size.x / 2.0f, size.y / 2.0f);
	shape->setPosition(0.0f, 0.0f);


	//create corners for physics component
	std::array<sf::Vector2f, 4> corners = std::array<sf::Vector2f, 4>();
	corners[0] = sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f);
	corners[1] = sf::Vector2f(size.x / 2.0f, -size.y / 2.0f);
	corners[2] = sf::Vector2f(size.x / 2.0f, size.y / 2.0f);
	corners[3] = sf::Vector2f(-size.x / 2.0f, size.y / 2.0f);

	auto input = new InputComponent();
	auto physics = new CarPhysicsComponent(startPos, MathCommon::DegreesToRadians(0.0f), corners);
	auto graphics = new CarGraphicsComponent(shape);
	auto collision = new CollisionComponent(startPos, 0.0f, corners);

	return new Entity(startPos, 0.0f, input, physics, graphics, collision);
}




