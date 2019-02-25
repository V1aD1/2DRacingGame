#pragma once

#include <SFML/Graphics.hpp>
#include "CarState.h"

class Entity;

class PhysicsComponent
{
public:
	static const float c_rotationSpeed;
	static const float c_acceleration;
	static const float c_brakeForce;
	static const float c_frictionForce;
	static const float c_dbg_slideSpeed;

public:
	PhysicsComponent(Entity* entity, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied);
	~PhysicsComponent();

	void Update(Entity& entity, float dtMilli);
	void Rotate(float degrees, bool left);
	void Accelerate(float dtTimeMilli, bool forward);
	void Brake(float dtTimeMilli);
	void DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli);
	const std::array<sf::Vector2f, 4>* GetWorldCorners() const;

private:
	bool CollisionDetected();
	void ApplySlowDownForce(float forceMag, float dtTimeMilli);
	void ApplyFriction(float dtTimeMilli);

private:
	CarState m_newState;
	CarState m_currState;
};

