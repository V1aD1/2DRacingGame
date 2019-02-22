#pragma once

#include <SFML/Graphics.hpp>

class CarState;

class PhysicsComponent
{
public:
	static const float c_length;
	static const float c_height;
	static const float c_rotationSpeed;
	static const float c_acceleration;
	static const float c_brakeForce;
	static const float c_frictionForce;
	static const float c_dbg_slideSpeed;
	static const float c_maxMomentum;

public:
	PhysicsComponent();
	~PhysicsComponent();

	void Update(CarState& currState, CarState& newState, float dtMilli);
	void Rotate(Entity& entity, float degrees, bool left);
	void Accelerate(float dtTimeMilli, bool forward);
	void Brake(float dtTimeMilli);
	void DBG_Slide(const sf::Vector2f& dir, float dtMilli);

private:
	bool CollisionDetected(const CarState& state);
	void ApplySlowDownForce(float forceMag, float dtTimeMilli);
	void ApplyFriction(float dtTimeMilli);

private:
	CarState newState;
	CarState currState;
};

