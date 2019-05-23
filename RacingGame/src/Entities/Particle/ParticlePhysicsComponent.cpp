#include "ParticlePhysicsComponent.h"
#include "../Entity.h"
#include "../../Other/MathCommon.h"

ParticlePhysicsComponent::ParticlePhysicsComponent() : 
	PhysicsComponent(sf::Vector2f(), 0, std::vector<sf::Vector2f>(), 0.3f, 180.0f, 0.5f, 0)
{
}

ParticlePhysicsComponent::~ParticlePhysicsComponent()
{
}

void ParticlePhysicsComponent::Update(Entity& entity, float dtMilli)
{
	//todo this is only temp testing for making particles look more random
	//todo will implement properly once proper physics is finished
	m_newState.Rotate(std::rand() % 10);
	//m_newState.SetRotation(MathCommon::DegreesToRadians(90));

	//////////////////////////////////////////////////////////////////////

	m_prevState = m_currState;
	m_newState.Update(dtMilli, m_maxSpeed);
	m_currState = m_newState;
	
	entity.SetPosition(m_currState.GetWorldPosition());
	entity.SetRotation(MathCommon::RadiansToDegrees(m_currState.GetRotInRad()));
}
