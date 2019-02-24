#define _USE_MATH_DEFINES
#include <cmath>

#include "include/Square.h"
#include "include/SquareGraphicsComponent.h"
#include "include/MathCommon.h"

//todo turn into a shape class that receives array of points as input
Square::Square(float sideLen, sf::Vector2f pos, float rot) 
{
	//todo this can be moved into a constructor in Entity
	m_position = pos;
	m_rotation = rot;
	m_rotationInRad = MathCommon::DegreesToRadians(rot);
	sideLength = sideLen;

	float halfSideLen = sideLength / 2;

	sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape->setOrigin(halfSideLen, halfSideLen);
	shape->setRotation(GetRotationInDegrees());
	shape->setPosition(GetPosition());
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


	//orienting corners according to Entity rotation
	for (int i = 0; i < localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = localCorners[i].x * std::cos(m_rotationInRad) - localCorners[i].y * std::sin(m_rotationInRad);
		newPoint.y = localCorners[i].x * std::sin(m_rotationInRad) + localCorners[i].y * std::cos(m_rotationInRad);

		//rotating the point about the centre of the shape
		localCorners[i] = newPoint;
	}

	for (int i = 0; i < localCorners.size(); i++) {
		worldCorners[i] = localCorners[i] + pos;
	}

	m_graphics = new SquareGraphicsComponent(shape, worldCorners);
	m_worldCorners = worldCorners;
}

//todo may not be necessary
Square::~Square()
{
}

const std::array<sf::Vector2f, 4>* Square::GetWorldCorners() const
{
	return &m_worldCorners;
}

