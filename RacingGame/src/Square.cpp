#define _USE_MATH_DEFINES
#include <cmath>

#include "include/Square.h"
#include "include/MathCommon.h"

//todo turn into a shape class that receives array of points as input
Square::Square(float sideLen, sf::Vector2f pos, float rot) : ConvexEntity(pos, rot)
{
	sideLength = sideLen;

	float halfSideLen = sideLength / 2;
	float rotInRad = MathCommon::DegreesToRadians(GetRotationInDegrees());

	sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape->setOrigin(halfSideLen, halfSideLen);
	shape->setRotation(GetRotationInDegrees());
	shape->setPosition(GetPosition());
	shape->setFillColor(sf::Color::Red);

	SetShape(shape);

	std::array<sf::Vector2f, 4> corners;

	//top left
	corners[0] = sf::Vector2f(-halfSideLen, -halfSideLen);

	//top right
	corners[1] = sf::Vector2f(halfSideLen, -halfSideLen);

	//bottom right
	corners[2] = sf::Vector2f(halfSideLen, halfSideLen);

	//bottom left
	corners[3] = sf::Vector2f(-halfSideLen, halfSideLen);

	SetCorners(corners);
}

Square::~Square()
{
	//todo not sure shape should be deleted here
	delete GetShape();
}

//this function should be moved out to a graphics component that draws to window
void Square::Update(sf::RenderWindow & window, float dtTimeMilli)
{
	//Rotate(0.01f * dtTimeMilli);

	float circleRad = 8.0f;

	window.draw(*GetShape());
	for(auto corner : GetWorldCorners())
	{
		auto circle = sf::CircleShape(circleRad);
		circle.setOrigin(circleRad, circleRad);
		circle.setPosition(corner);
		window.draw(circle);
	}
}

