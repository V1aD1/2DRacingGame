#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include "include/Car.h"
#include "include/MathCommon.h"
#include "include/Square.h"
#include "include/EventHandler.h"

const float Car::c_length = 40.0f;
const float Car::c_height = 10.0f;

const float Car::c_rotationSpeed = 180.0f;
const float Car::c_acceleration = 0.25f;
const float Car::c_brakeForce = 0.1f;
const float Car::c_frictionForce = 0.1f;
const float Car::c_dbg_slideSpeed = 150.0f;
const float Car::c_maxMomentum = 0.3f;

Car::Car(sf::Vector2f startPos) : newState(startPos, 0.0f, sf::Vector2f(c_length, c_height)), 
								  currState(startPos, 0.0f, sf::Vector2f(c_length, c_height)){}

void Car::Rotate(float dtTimeMilli, bool left)
{
	int direction = left ? -1 : 1;

	float rotAmount = direction * c_rotationSpeed * (dtTimeMilli / 1000.0f);

	newState.Rotate(rotAmount);

	newState.forwardDir = sf::Vector2f(std::cos(newState.GetRotationInRadians()), std::sin(newState.GetRotationInRadians()));
}

void Car::Accelerate(float dtTimeMilli, bool forward)
{
	if (forward)
		newState.momentum += newState.forwardDir * c_acceleration * (dtTimeMilli / 1000.0f);
	else
		newState.momentum += -(newState.forwardDir * c_acceleration * (dtTimeMilli / 1000.0f));
}

void Car::Brake(float dtTimeMilli)
{
	ApplySlowDownForce(c_brakeForce, dtTimeMilli);
}

void Car::DBG_Slide(const sf::Vector2f& dir, float dtMilli)
{
	//halting all movement on the car
	newState.momentum = sf::Vector2f(0.0f, 0.0f);
	currState.momentum = sf::Vector2f(0.0f, 0.0f);
	
	//placing car to exact position
	currState.SetPosition(currState.GetPosition() + dir * dtMilli / 1000.0f * c_dbg_slideSpeed);
	newState.SetPosition(currState.GetPosition());
}

void Car::ApplyFriction(float dtTimeMilli)
{
	ApplySlowDownForce(c_frictionForce, dtTimeMilli);
}

void Car::ApplySlowDownForce(float forceMag, float dtTimeMilli)
{
	sf::Vector2f momentumDir = MathCommon::Normalize(newState.momentum);
	sf::Vector2f stoppingForceToApply = MathCommon::Normalize(newState.momentum) * forceMag * (dtTimeMilli / 1000.0f);

	float momentumMag = MathCommon::GetMagnitude(newState.momentum);
	float stoppingForceMag = MathCommon::GetMagnitude(stoppingForceToApply);

	//to ensure stopping force doesn't cause car to move backwards
	if (momentumMag > stoppingForceMag)
		newState.momentum -= stoppingForceToApply;
	else
		newState.momentum = sf::Vector2f(0.0f, 0.0f);
}

void Car::Update(sf::RenderWindow& window, float dtTimeMilli, EventHandler& handler)
{
	//input->Update(*this, handler, dtTimeMilli);
	//physics->Update(currState, newState, dtTimeMilli);
	//graphics->Update(currState, window);
}

Car::~Car() {
}