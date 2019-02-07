#define _USE_MATH_DEFINES
#include <cmath>

#include "include/Square.h"
#include "include/MathCommon.h"

//todo turn into a shape class that receives array of points as input
Square::Square(float sideLen, sf::Vector2f pos, float rot) : Entity(pos, rot)
{
	sideLength = sideLen;
	m_rotation = rot;
	m_position = pos;
	float halfSideLen = sideLength / 2;
	float rotInRad = MathCommon::DegreesToRadians(m_rotation);

	sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape->setOrigin(halfSideLen, halfSideLen);
	shape->setRotation(m_rotation);
	shape->setPosition(m_position);
	shape->setFillColor(sf::Color::Red);

	m_shape = shape;

	//top left
	m_localCorners[0] = sf::Vector2f(-halfSideLen, -halfSideLen);

	//top right
	m_localCorners[1] = sf::Vector2f(halfSideLen, -halfSideLen);

	//bottom right
	m_localCorners[2] = sf::Vector2f(halfSideLen, halfSideLen);

	//bottom left
	m_localCorners[3] = sf::Vector2f(-halfSideLen, halfSideLen);

	for (int i = 0; i < 4; i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(rotInRad) - m_localCorners[i].y * std::sin(rotInRad);
		newPoint.y = m_localCorners[i].x * std::sin(rotInRad) + m_localCorners[i].y * std::cos(rotInRad);

		//rotating the point about the centre of the square
		m_localCorners[i] = newPoint;
	}

}


Square::~Square()
{
	delete m_shape;
}

void Square::Update(sf::RenderWindow & window, float dtTimeMilli)
{
	float circleRad = 8.0f;

	window.draw(*m_shape);
	for(auto corner : GetWorldCorners())
	{
		auto circle = sf::CircleShape(circleRad);
		circle.setOrigin(circleRad, circleRad);
		circle.setPosition(corner);
		window.draw(circle);
	}
}
