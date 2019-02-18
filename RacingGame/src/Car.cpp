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
								  currState(startPos, 0.0f, sf::Vector2f(c_length, c_height)), 
								  input(new InputComponent()){}

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

///NOTE: function should only be called after computing 
///final position of newState
bool Car::CollisionDetected() {
	//check every static object for a collision
	//using point triangle test method
	for (auto object : G_STATICOBJECTS) {
		std::array<sf::Vector2f, 4> objCorners = (*object).GetWorldCorners();

		for (auto &carCorner : newState.GetWorldCorners()) {

			bool collision = true;

			for (size_t i = 0; i < objCorners.size(); i++) {
				
				//this operation must be performed in this order!!
				float check = MathCommon::CrossProduct(objCorners[i] - objCorners[(i + 1)% objCorners.size()], objCorners[i] - carCorner);

				if (check < 0.0f) {
					collision = false;
					break;
				}
				//todo handle check == 0
			}

			if(collision)
				return true;
		}
	}

	return false;
}

void Car::Update(sf::RenderWindow& window, float dtTimeMilli, EventHandler& handler)
{
	input->Update(*this, handler, dtTimeMilli);

	ApplyFriction(dtTimeMilli);

	if (MathCommon::GetMagnitude(newState.momentum) > c_maxMomentum)
		newState.momentum = MathCommon::ChangeLength(newState.momentum, c_maxMomentum);

	//this calculation MUST ONLY happen in Update() to enusre
	//position isn't getting updated multiple times
	newState.SetPosition(newState.GetPosition() + newState.momentum * dtTimeMilli);

	//update to new state only if NO collision occured
	if (!CollisionDetected())
		currState.UpdateToNewState(newState);
	

	else {
		//if collision occurs then halt all momentum on the car
		currState.momentum = sf::Vector2f(0.0f, 0.0f);

		newState.UpdateToNewState(currState);
	}

	auto corners = currState.GetWorldCorners();

	//drawing corners of car
	float circleRad = 2.0f;
	for (int i = 0; i < corners.size(); i++)
	{
		//so corners are visible
		auto circle = sf::CircleShape(circleRad);
		circle.setOrigin(circleRad, circleRad);
		circle.setPosition(corners[i]);
		window.draw(circle);
	}

	window.draw(*currState.GetShape());
}

Car::~Car() {
}