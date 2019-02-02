#define _USE_MATH_DEFINES
#include <cmath>

#include "include/Square.h"
#include "include/MathCommon.h"

//todo turn into a shape class that receives array of points as input
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
	corners[0] = sf::Vector2f(-halfSideLen, -halfSideLen);

	//top right
	corners[1] = sf::Vector2f(halfSideLen, -halfSideLen);

	//bottom right
	corners[2] = sf::Vector2f(halfSideLen, halfSideLen);

	//bottom left
	corners[3] = sf::Vector2f(-halfSideLen, halfSideLen);

	for (int i = 0; i < 4; i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = corners[i].x * std::cos(rotInRad) - corners[i].y * std::sin(rotInRad);
		newPoint.y = corners[i].x * std::sin(rotInRad) + corners[i].y * std::cos(rotInRad);

		//rotating the point about the centre of the square
		corners[i] = newPoint;

		//moving the point to it's world space coordinates
		corners[i] += position;
	}

	//setting collision info
	collisionChecks[0] = MathCommon::CrossProduct(corners[0] - corners[1], corners[0] - position) > 0.0f ? true : false;
	collisionChecks[1] = MathCommon::CrossProduct(corners[1] - corners[2], corners[1] - position) > 0.0f ? true : false;
	collisionChecks[2] = MathCommon::CrossProduct(corners[2] - corners[3], corners[2] - position) > 0.0f ? true : false;
	collisionChecks[3] = MathCommon::CrossProduct(corners[3] - corners[0], corners[3] - position) > 0.0f ? true : false;

}

void Square::Update(sf::RenderWindow & window, float dtTimeMilli)
{

	float circleRad = 8.0f;

	window.draw(shape);
	for(int i =0 ; i< 4; i++)
	{
		auto circle = sf::CircleShape(circleRad);
		circle.setOrigin(circleRad, circleRad);
		circle.setPosition(corners[i]);
		window.draw(circle);
	}
}

std::array<sf::Vector2f, 4> Square::GetCorners()
{
	return corners;
}

std::array<bool, 4> Square::GetCollisionChecks()
{
	return collisionChecks;
}

Square::~Square()
{
}
