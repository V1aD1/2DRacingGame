/*#pragma once
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

class Entity;
class CarState;

class PhysicsEntity : public Entity
{
public:
	PhysicsEntity(sf::Vector2f pos, float rot, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
	~PhysicsEntity();

	//void Rotate(float degrees, bool left);
	void Accelerate(float dtTimeMilli, bool forward);
	void Brake(float dtTimeMilli);
	void DBG_Slide(const sf::Vector2f& dir, float dtMilli);

private:
	float m_acceleration;
	float m_rotationSpeed;
	float m_brakeForce;
	float m_frictionForce;
	float m_dbg_slideSpeed;

	sf::Vector2f forwardDir = sf::Vector2f(1.0f, 0.0f);
	sf::Vector2f momentum = sf::Vector2f(0.0f, 0.0f);

	CarState m_newState;
	CarState m_currState;
};

*/