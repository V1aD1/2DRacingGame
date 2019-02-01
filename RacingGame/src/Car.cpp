#include <iostream>

#include <SFML/Graphics.hpp>

#include "include/Car.h"
#include "include/MathCommon.h"

const float Car::length = 40.0f;
const float Car::height = 10.0f;

Car::Car()
{
	shape = sf::RectangleShape(sf::Vector2f(length, height));
	shape.setFillColor(sf::Color::Blue);
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	shape.setOrigin(length/2.0f, height/2.0f);
	//shape.setPosition(0.0f, 0.0f);


	corners[0] = sf::Vector2f(-length / 2.0f, -height / 2.0f);
	corners[1] = sf::Vector2f(length / 2.0f, -height / 2.0f);
	corners[2] = sf::Vector2f(length / 2.0f, height / 2.0f);
	corners[3] = sf::Vector2f(-length / 2.0f, height / 2.0f);

}

Car::Car(const Car & car)
{
	acceleration = car.acceleration;
	brakeForce = car.brakeForce;
	
	for(int i = 0; i< 4; i++)
		corners[i] = car.corners[i];

	currPos = car.currPos;
	//car.dbg_slideSpeed;
	forwardDir = car.forwardDir;
	frictionForce = car.frictionForce;
	//car.height;
	//car.length;
	//car.maxMomentum;
	momentum = car.momentum;
	rotationSpeed = car.rotationSpeed;
	rotDeg = car.rotDeg;
	rotRad = car.rotRad;
	shape = car.shape;
}

Car::Car(sf::Vector2f startPos) : Car()
{
	currPos = startPos;
}

void Car::Rotate(float dtTimeMilli, bool left)
{
	int direction = left ? -1 : 1;

	float rotAmount = direction * rotationSpeed * (dtTimeMilli / 1000.0f);
	float rotAmountRad = MathCommon::DegreesToRadians(rotAmount);

	rotDeg += rotAmount;
	rotRad = MathCommon::DegreesToRadians(rotDeg);


	//determine new direction vector based on new rotation
	forwardDir = sf::Vector2f(std::cos(rotRad), std::sin(rotRad));

	for (int i = 0; i < 4; i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = corners[i].x * std::cos(rotAmountRad) - corners[i].y * std::sin(rotAmountRad);
		newPoint.y = corners[i].x * std::sin(rotAmountRad) + corners[i].y * std::cos(rotAmountRad);

		corners[i] = newPoint;
	}
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
	shape.move(dir * dtMilli / 1000.0f * dbg_slideSpeed);
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

	currPos += momentum * dtTimeMilli;
	shape.setRotation(rotDeg);
	shape.setPosition(currPos);

	window.draw(shape);

	float circleRad = 2.0f;
	for (int i = 0; i< 4; i++)
	{
		//so corners are visible
		auto circle = sf::CircleShape(circleRad);
		circle.setOrigin(circleRad, circleRad);
		circle.setPosition(corners[i] + currPos);
		window.draw(circle);
	}
}

Car::~Car()
{
}
