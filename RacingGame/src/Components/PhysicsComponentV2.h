#pragma once

#include <tuple>
#include <SFML/Graphics.hpp>
#include "PhysicsStateV2.h"

class Entity;

class PhysicsComponentV2
{
public:
	PhysicsComponentV2(sf::Vector2f pos,
		float rotRad,
		const std::vector<sf::Vector2f>& cornersWithoutRotationApplied,
		float maxSpeed,
		float rotSpeed,
		float acceleration,
		float frictionVelocity);
	~PhysicsComponentV2();

public:
	virtual void Rotate(float degrees, bool left);
	virtual void Accelerate(float dtTimeMilli, bool forward);
	virtual void ApplyFriction(float dtTimeMilli);

	virtual void SetSpeed(float newSpeed);
	virtual void SetPosition(sf::Vector2f newPos);
	virtual void SetRotation(float newRotInRad);

	virtual void Update(Entity& entity, float dtMilli) = 0;
	virtual void Brake(float dtTimeMilli) = 0;
	virtual void DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli) = 0;

	const std::vector<sf::Vector2i>& GetCollisionSpaceCoords();
	const std::vector<sf::Vector2i>& GetPrevCollisionSpaceCoords();
	sf::Vector2f GetForwardDir();

	virtual sf::Vector2f HandleCollision(sf::Vector2f otherEntityMomentum) = 0;


protected:
	PhysicsStateV2 m_prevState;
	PhysicsStateV2 m_newState;
	PhysicsStateV2 m_currState;

protected:
	std::tuple<Entity*, sf::Vector2f> CollisionDetected(Entity& entity);
	void ApplySlowDownVelocity(float velocityMag, float dtTimeMilli);

protected:
	float m_maxSpeed;
	float m_rotationSpeed;
	float m_acceleration;
	float m_frictionVelocity;
	float m_dbg_slideSpeed = 150.0f;
};

