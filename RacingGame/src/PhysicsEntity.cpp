/*#include "include/PhysicsEntity.h"

#include "include/InputComponent.h"
#include "include/PhysicsComponent.h"
#include "include/Entity.h"
#include "include/GraphicsComponent.h"
#include "include/CarState.h"

PhysicsEntity::PhysicsEntity(sf::Vector2f pos,
							 float rot, InputComponent * input, 
						     PhysicsComponent * physics, 
							 GraphicsComponent * graphics):
							 Entity(pos, rot, input, physics, graphics), 
							 m_currState(CarState(pos, rot, sf::Vector2f(PhysicsComponent::c_length, PhysicsComponent::c_height))),
							 m_newState(CarState(pos, rot, sf::Vector2f(PhysicsComponent::c_length, PhysicsComponent::c_height))){}

PhysicsEntity::~PhysicsEntity(){}

void PhysicsEntity::Accelerate(float dtTimeMilli, bool forward)
{
	if (forward)
		m_newState.momentum += m_newState.forwardDir * m_acceleration * (dtTimeMilli / 1000.0f);
	else
		m_newState.momentum += -(m_newState.forwardDir * m_acceleration * (dtTimeMilli / 1000.0f));
}

void PhysicsEntity::Brake(float dtTimeMilli)
{
	m_newState.ApplySlowDownForce(m_brakeForce, dtTimeMilli);
}

void PhysicsEntity::DBG_Slide(const sf::Vector2f& dir, float dtMilli)
{
	//halting all movement on the car
	m_newState.momentum = sf::Vector2f(0.0f, 0.0f);
	m_currState.momentum = sf::Vector2f(0.0f, 0.0f);

	//placing car to exact position
	m_currState.SetPosition(m_currState.GetPosition() + dir * dtMilli / 1000.0f * m_dbg_slideSpeed);
	m_newState.SetPosition(m_currState.GetPosition());
}*/