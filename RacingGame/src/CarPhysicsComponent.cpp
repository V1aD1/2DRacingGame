#include "include/CarPhysicsComponent.h"
#include "include/Entity.h"
#include "include/MathCommon.h"

const float CarPhysicsComponent::car_rotationSpeed = 180.0f;
const float CarPhysicsComponent::car_acceleration = 0.25f;
const float CarPhysicsComponent::car_brakeForce = 0.1f;
const float CarPhysicsComponent::car_frictionForce = 0.1f;
const float CarPhysicsComponent::car_dbg_slideSpeed = 150.0f;
const float CarPhysicsComponent::car_maxMomentum = 0.3f;

CarPhysicsComponent::CarPhysicsComponent(sf::Vector2f pos, float rotRad, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied) :
						PhysicsComponent(pos, 
										rotRad, 
										cornersWithoutRotationApplied, 
										car_maxMomentum,
										car_rotationSpeed, 
										car_acceleration, 
										car_brakeForce, 
										car_frictionForce, 
										car_dbg_slideSpeed)
{
}


CarPhysicsComponent::~CarPhysicsComponent()
{
}

void CarPhysicsComponent::Update(Entity& entity, float dtMilli)
{
	m_prevState = m_currState;
	
	ApplyFriction(dtMilli);

	m_newState.Update(dtMilli, car_maxMomentum);

	//update to new state only if NO collision occured
	if (!CollisionDetected(entity)) 
		m_currState = m_newState;
	

	//if collision occurs then halt all momentum on the car
	//and do NOT apply new state
	else {
		m_currState.SetMomentum(sf::Vector2f(0.0f, 0.0f));
		m_newState = m_currState;
	}

	entity.SetPosition(m_currState.GetWorldPosition());
	entity.SetRotation(MathCommon::RadiansToDegrees(m_currState.GetRotInRad()));
}

void CarPhysicsComponent::Brake(float dtTimeMilli)
{
	ApplySlowDownForce(car_brakeForce, dtTimeMilli);
}

void CarPhysicsComponent::DBG_Slide(Entity & entity, const sf::Vector2f & dir, float dtMilli)
{
	//halting all movement on the car
	m_newState.SetMomentum(sf::Vector2f(0.0f, 0.0f));
	m_newState.SetWorldPos(m_newState.GetWorldPosition() + dir * dtMilli / 1000.0f * car_dbg_slideSpeed);
	m_newState.Update(dtMilli, car_maxMomentum);

	m_prevState = m_currState;
	m_currState = m_newState;
}
