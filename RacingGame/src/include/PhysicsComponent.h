#pragma once

#include <SFML/Graphics.hpp>

class CarState;

class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	void Update(CarState& currState, CarState& newState, float dtMilli);

private:
	bool CollisionDetected(const CarState& state);
};

