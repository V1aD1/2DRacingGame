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
	Accelerate(dtMilli, true);
	
	if(m_randRotRange > 0)
		m_newState.Rotate(std::rand() % m_randRotRange);

	m_prevState = m_currState;
	m_newState.Update(dtMilli, m_maxSpeed);
	m_currState = m_newState;
	
	PhysicsComponent::Update(entity, dtMilli);
}

void ParticlePhysicsComponent::SetRandomness(int newRand)
{
	m_randRotRange = newRand;
}
