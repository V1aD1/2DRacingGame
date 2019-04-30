#pragma once

#include <SFML/Graphics.hpp>
#include "PhysicsState.h"

class Entity;

class PhysicsComponent
{
public:
	PhysicsComponent(sf::Vector2f pos, 
					float rotRad,
					const std::vector<sf::Vector2f>& cornersWithoutRotationApplied,
					float maxMomentum,
					float rotSpeed,
					float acceleration,
					float brakeForce,
					float frictionForce,
					float dbg_slideSpeed);
	~PhysicsComponent();

public:
	virtual void Rotate(float degrees, bool left);
	virtual void Accelerate(float dtTimeMilli, bool forward);
	virtual void ApplyFriction(float dtTimeMilli);

	virtual void SetSpeed(float newSpeed);

	virtual void Update(Entity& entity, float dtMilli) = 0;
	virtual void Brake(float dtTimeMilli) = 0;
	virtual void DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli) = 0;
	
	const std::vector<sf::Vector2i>& GetCollisionSpaceCoords();
	const std::vector<sf::Vector2i>& GetPrevCollisionSpaceCoords();

	virtual sf::Vector2f HandleCollision(sf::Vector2f otherEntityMomentum) = 0;


protected:
	PhysicsState m_prevState;
	PhysicsState m_newState;
	PhysicsState m_currState;

protected:
	Entity* CollisionDetected(Entity& entity);
	void ApplySlowDownForce(float forceMag, float dtTimeMilli);

private:	
	float m_maxMomentum;
	float m_rotationSpeed;
	float m_acceleration;
	float m_brakeForce;
	float m_frictionForce;
	float m_dbg_slideSpeed;
};

