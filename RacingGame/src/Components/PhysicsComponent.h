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
	void Rotate(float degrees, bool left);
	void Accelerate(float dtTimeMilli, bool forward);
	void Decelerate(float dtTimeMilli);
	void ApplyFriction(float dtTimeMilli);

	//only needed in CarPhysics but that's the composition pattern for you!
	virtual void Brake(Entity& entity, float dtTimeMilli);

	void SetSpeed(float newSpeed);
	void SetMaxSpeed(float newMaxSpeed);
	void SetPosition(sf::Vector2f newPos);
	void SetRotation(float newRotInRad);
	void SetAcceleration(float newAcc);
	virtual void SetRandomness(int newRand);

	virtual void Update(Entity& entity, float dtMilli);
	virtual void DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli);
	virtual sf::Vector2f HandleCollision(sf::Vector2f otherEntityVelocity);

	const std::vector<sf::Vector2i>& GetCollisionSpaceCoords() const;
	const std::vector<sf::Vector2i>& GetPrevCollisionSpaceCoords() const;

	sf::Vector2f GetForwardDir();


protected:
	PhysicsState m_prevState;
	PhysicsState m_newState;
	PhysicsState m_currState;

protected:
	std::tuple<Entity*, sf::Vector2f> DetectCollision(Entity& self);
	Entity* DetectCollisionLineTest(Entity& self);
	void SlowDown(float deceleration, float dtTimeMilli);

protected:
	float m_maxSpeed;
	float m_rotationSpeed;
	float m_acceleration;
	float m_frictionDeceleration;
	float m_dbg_slideSpeed = 150.0f;
};

