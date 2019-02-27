#define _USE_MATH_DEFINES
#include <cmath>

#include "include/Square.h"
#include "include/SquareGraphicsComponent.h"
#include "include/MathCommon.h"
#include "include/CollisionComponent.h"

//todo turn into a shape class that receives array of points as input
Square::Square(float sideLen, sf::Vector2f pos, float rotDeg) : Entity(pos, rotDeg){
	float halfSideLen = sideLen / 2;

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

	auto currentRotRad = GetRotationInRadians();


	m_collision = new CollisionComponent(pos, currentRotRad, localCorners);
	m_graphics = new SquareGraphicsComponent(shape);
}

Square::~Square(){}

