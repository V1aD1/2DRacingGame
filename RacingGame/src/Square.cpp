#define _USE_MATH_DEFINES
#include <cmath>

#include "include/Square.h"
#include "include/MathCommon.h"


Square::Square(float sideLen, sf::Vector2f pos, float rot)
{
	sideLength = sideLen;
	rotation = rot;
	position = pos;
	float halfSideLen = sideLength / 2;
	float rotInRad = MathCommon::DegreesToRadians(rotation);

	shape = sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape.setOrigin(halfSideLen, halfSideLen);
	shape.setRotation(rotation);
	shape.setPosition(position);
	shape.setFillColor(sf::Color::Red);

	//top left
	points[0] = sf::Vector2f(-halfSideLen, -halfSideLen);

	//top right
	points[1] = sf::Vector2f(halfSideLen, -halfSideLen);

	//bottom right
	points[2] = sf::Vector2f(halfSideLen, halfSideLen);

	//bottom left
	points[3] = sf::Vector2f(-halfSideLen, halfSideLen);

	for (int i = 0; i < 4; i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = points[i].x * std::cos(rotInRad) - points[i].y * std::sin(rotInRad);
		newPoint.y = points[i].x * std::sin(rotInRad) + points[i].y * std::cos(rotInRad);

		//rotating the point about the centre of the square
		points[i] = newPoint;


		//moving the point to it's world space coordinates
		points[i] += position;
	}
}

void Square::Update(sf::RenderWindow & window, float dtTimeMilli)
{

	float circleRad = 8.0f;

	window.draw(shape);
	for(int i =0 ; i< 4; i++)
	{
		auto circle = sf::CircleShape(circleRad);
		circle.setOrigin(circleRad, circleRad);
		circle.setPosition(points[i]);
		window.draw(circle);
	}
}


Square::~Square()
{
}
