#include "include/EntityFactory.h"
#include "include/Entity.h"
#include "include/SquareGraphicsComponent.h"
#include "include/MathCommon.h"

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

	//top left
	localCorners[0] = sf::Vector2f(-halfSideLen, -halfSideLen);

	//top right
	localCorners[1] = sf::Vector2f(halfSideLen, -halfSideLen);

	//bottom right
	localCorners[2] = sf::Vector2f(halfSideLen, halfSideLen);

	//bottom left
	localCorners[3] = sf::Vector2f(-halfSideLen, halfSideLen);

	auto graphicsCom = new SquareGraphicsComponent(shape);
	auto collisionCom = new CollisionComponent(pos, MathCommon::DegreesToRadians(rotDeg), localCorners);

	return new Entity(pos, rotDeg, nullptr, nullptr, graphicsCom, collisionCom);
}

Entity * EntityFactory::CreateCar(sf::Vector2f pos)
{
	return nullptr;
}




