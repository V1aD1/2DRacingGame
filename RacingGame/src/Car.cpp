#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "include/Car.h"


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
	
	rotRad = (rotDeg * M_PI) / 180.0f;

	//determine new direction vector base on new rotation
	forwardDir = sf::Vector2f(std::cos(rotRad), std::sin(rotRad));
}

void Car::Accelerate(float dtTimeMilli, bool forward)
{
	if(forward)
		currentSpeed = std::min(currentSpeed + (acceleration * (dtTimeMilli / 1000.0f)), maxSpeed);
	else
		currentSpeed = std::max(currentSpeed + (-acceleration * (dtTimeMilli / 1000.0f)), -maxSpeed/2);
}

void Car::Update(sf::RenderWindow& window, float dtTimeMilli)
{
	float dtSec = dtTimeMilli / 1000.0f;
	shape.move(currentSpeed * forwardDir.x * dtSec, currentSpeed * forwardDir.y * dtSec);
	std::cout << "Forward vector: " << forwardDir.x << ", " << forwardDir.y << std::endl;
	//std::cout << rotation << std::endl;
	window.draw(shape);
}


Car::~Car()
{
}
