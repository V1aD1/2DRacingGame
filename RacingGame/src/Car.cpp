#include <iostream>

#include <SFML/Graphics.hpp>

#include "include/Car.h"
#include "include/MathCommon.h"

Car::Car()
{
	shape = sf::RectangleShape(sf::Vector2f(40.0f, 10.0f));
	shape.setFillColor(sf::Color::Blue);
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	shape.setOrigin(20.0f, 5.0f);
	shape.setPosition(0.0f, 0.0f);
}

Car::Car(float posX, float posY)
{
	shape = sf::RectangleShape(sf::Vector2f(40.0f, 10.0f));
	shape.setFillColor(sf::Color::Blue);
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	shape.setOrigin(20.0f, 5.0f);
	shape.setPosition(posX, posY);
}

void Car::Rotate(float dtTimeMilli, bool left)
{
	int direction = 1;
	if (left) { direction = -1; }
	
	rotDeg += direction * rotationSpeed * (dtTimeMilli / 1000.0f);
	shape.setRotation(rotDeg);
	
	rotRad = MathCommon::DegreesToRadians(rotDeg);

	//determine new direction vector base on new rotation
	forwardDir = sf::Vector2f(std::cos(rotRad), std::sin(rotRad));
}

void Car::Accelerate(float dtTimeMilli, bool forward)
{
	if (forward)
		momentum += forwardDir * acceleration * (dtTimeMilli / 1000.0f);
	else
		momentum += -(forwardDir * acceleration * (dtTimeMilli / 1000.0f));

	if(MathCommon::GetMagnitude(momentum) > maxMomentum)
		momentum = MathCommon::ChangeLength(momentum, maxMomentum);
}

void Car::Update(sf::RenderWindow& window, float dtTimeMilli)
{
	shape.move(momentum * dtTimeMilli);
	std::cout << "momentum: " << MathCommon::GetMagnitude(momentum) << std::endl;

	window.draw(shape);
}


Car::~Car()
{
}
