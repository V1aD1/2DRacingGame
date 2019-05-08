#pragma once

#include <tuple>
#include <SFML/Graphics.hpp>
#include "PhysicsState.h"

class Entity;

class PhysicsComponent
{
public:
	PhysicsComponent(sf::Vector2f pos,
		float rotRad,
		const std::vector<sf::Vector2f>& cornersWithoutRotationApplied,
		float maxSpeed,
		float rotSpeed,
		float acceleration,
		float frictionDeceleration);
	~PhysicsComponent();

public:
	virtual void Rotate(float degrees, bool left);
	virtual void Accelerate(float dtTimeMilli, bool forward);
	virtual void ApplyFriction(float dtTimeMilli);

	//todo this should only be in the car physics component,
	//but that'd require a new CarEntity object....
	virtual void Brake(float dtTimeMilli);

	virtual void SetSpeed(float newSpeed);
	virtual void SetPosition(sf::Vector2f newPos);
	virtual void SetRotation(float newRotInRad);

	virtual void Update(Entity& entity, float dtMilli) = 0;
	virtual void DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli) = 0;

	const std::vector<sf::Vector2i>& GetCollisionSpaceCoords();
	const std::vector<sf::Vector2i>& GetPrevCollisionSpaceCoords();
	sf::Vector2f GetForwardDir();

	virtual sf::Vector2f HandleCollision(sf::Vector2f otherEntityVelocity) = 0;


protected:
	PhysicsState m_prevState;
	PhysicsState m_newState;
	PhysicsState m_currState;

protected:
	std::tuple<Entity*, sf::Vector2f> CollisionDetected(Entity& entity);

	//todo correctly implement this function once acceleration is figured out
	void SlowDown(float deceleration, float dtTimeMilli);

protected:
	float m_maxSpeed;
	float m_rotationSpeed;

	//todo make acceleration a vector2f
	float m_acceleration;
	float m_frictionDeceleration;
	float m_dbg_slideSpeed = 150.0f;
};

