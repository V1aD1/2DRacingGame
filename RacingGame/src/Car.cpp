#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include "include/Car.h"
#include "include/MathCommon.h"
#include "include/Square.h"

const float Car::c_length = 40.0f;
const float Car::c_height = 10.0f;

const float Car::c_rotationSpeed = 180.0f;
const float Car::c_acceleration = 0.25f;
const float Car::c_brakeForce = 0.1f;
const float Car::c_frictionForce = 0.1f;
const float Car::c_dbg_slideSpeed = 150.0f;
const float Car::c_maxMomentum = 0.3f;

Car::Car(sf::Vector2f startPos) : shape(sf::Vector2f(c_length, c_height))
{
	shape.setFillColor(sf::Color::Blue);
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	shape.setOrigin(c_length / 2.0f, c_height / 2.0f);
	shape.setPosition(0.0f, 0.0f);

	newState.corners[0] = sf::Vector2f(-c_length / 2.0f, -c_height / 2.0f);
	newState.corners[1] = sf::Vector2f(c_length / 2.0f, -c_height / 2.0f);
	newState.corners[2] = sf::Vector2f(c_length / 2.0f, c_height / 2.0f);
	newState.corners[3] = sf::Vector2f(-c_length / 2.0f, c_height / 2.0f);

	newState.position = startPos;

	currState = newState;
}

void Car::Rotate(float dtTimeMilli, bool left)
{
	int direction = left ? -1 : 1;

	float rotAmount = direction * c_rotationSpeed * (dtTimeMilli / 1000.0f);
	float rotAmountRad = MathCommon::DegreesToRadians(rotAmount);

	newState.rotDeg = currState.rotDeg + rotAmount;
	newState.rotRad = MathCommon::DegreesToRadians(newState.rotDeg);


	//determine new direction vector based on new rotation
	newState.forwardDir = sf::Vector2f(std::cos(newState.rotRad), std::sin(newState.rotRad));

	for (int i = 0; i < 4; i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = newState.corners[i].x * std::cos(rotAmountRad) - newState.corners[i].y * std::sin(rotAmountRad);
		newPoint.y = newState.corners[i].x * std::sin(rotAmountRad) + newState.corners[i].y * std::cos(rotAmountRad);

		newState.corners[i] = newPoint;
	}
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
	currState.position += dir * dtMilli / 1000.0f * c_dbg_slideSpeed;
	newState.position = currState.position;


	//shape.move(dir * dtMilli / 1000.0f * c_dbg_slideSpeed);
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
	
	std::array<sf::Vector2f, 4> carWorldCorners;

	//set corners to world coordinates
	for (size_t i = 0; i < 4; i++) {
		carWorldCorners[i] = newState.corners[i] + newState.position;
	}

	//check every static object for a collision
	//using point triangle test method
	for (auto &object : G_STATICOBJECTS) {
		std::array<sf::Vector2f, 4> objCorners = object.GetCorners();
		std::array<bool, 4> objCollisionChecks = object.GetCollisionChecks();
		
		for (auto &carCorner : carWorldCorners) {

			bool collision = true;
			for (size_t i = 0; i < objCorners.size()-1; i++) {
				
				//this operation must be performed in this order!!
				float check = MathCommon::CrossProduct(objCorners[i] - objCorners[i + 1], objCorners[i] - carCorner);

				if (check > 0.0f && !objCollisionChecks[i]) {
					collision = false;
					break;
				}
				else if (check < 0.0f && objCollisionChecks[i]) {
					collision = false;
					break;
				}
				//todo handle check == 0
			}

			//point is on same side of object as it's origin,
			//therefore collision occurs
			if (collision == true)
				return true;
		}
	}

	return false;
}

void Car::Update(sf::RenderWindow& window, float dtTimeMilli)
{
	ApplyFriction(dtTimeMilli);

	if (MathCommon::GetMagnitude(newState.momentum) > c_maxMomentum)
		newState.momentum = MathCommon::ChangeLength(newState.momentum, c_maxMomentum);

	//this calculation MUST ONLY happen in Update() to enusre
	//position isn't getting updated multiple times
	newState.position += newState.momentum * dtTimeMilli;

	//update to new state only if NO collision occured
	std::cout << CollisionDetected() << std::endl;
	if (!CollisionDetected())
	{
		currState = newState;

		shape.setRotation(currState.rotDeg);
		shape.setPosition(currState.position);

		window.draw(shape);

		//drawing corners of car
		float circleRad = 2.0f;
		for (int i = 0; i < 4; i++)
		{
			//so corners are visible
			auto circle = sf::CircleShape(circleRad);
			circle.setOrigin(circleRad, circleRad);
			circle.setPosition(currState.corners[i] + currState.position);
			window.draw(circle);
		}
	}
}

Car::~Car()
{
}
