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

Car::Car(sf::Vector2f pos)
{
	shape = sf::RectangleShape(sf::Vector2f(40.0f, 10.0f));
	shape.setFillColor(sf::Color::Blue);
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	shape.setOrigin(20.0f, 5.0f);
	shape.setPosition(pos);
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
}

void Car::Brake(float dtTimeMilli)
{
	ApplySlowDownForce(brakeForce, dtTimeMilli);
}

void Car::DBG_Slide(const sf::Vector2f& dir, float dtMilli)
{
	momentum = sf::Vector2f(0.0f, 0.0f);
	shape.move(dir * dtMilli/1000.0f * dbg_slideSpeed);
}

void Car::ApplyFriction(float dtTimeMilli)
{
	ApplySlowDownForce(frictionForce, dtTimeMilli);
}

void Car::ApplySlowDownForce(float forceMag, float dtTimeMilli)
{
	sf::Vector2f momentumDir = MathCommon::Normalize(momentum);
	sf::Vector2f stoppingForceToApply = MathCommon::Normalize(momentum) * forceMag * (dtTimeMilli / 1000.0f);

	float momentumMag = MathCommon::GetMagnitude(momentum);
	float stoppingForceMag = MathCommon::GetMagnitude(stoppingForceToApply);

	//to ensure stopping force doesn't cause car to move backwards
	if (momentumMag > stoppingForceMag)
		momentum -= stoppingForceToApply;
	else
		momentum = sf::Vector2f(0.0f, 0.0f);
}

void Car::Update(sf::RenderWindow& window, float dtTimeMilli)
{
	ApplyFriction(dtTimeMilli);

	if (MathCommon::GetMagnitude(momentum) > maxMomentum)
		momentum = MathCommon::ChangeLength(momentum, maxMomentum);

	shape.move(momentum * dtTimeMilli);

	window.draw(shape);
}

Car::~Car()
{
}
