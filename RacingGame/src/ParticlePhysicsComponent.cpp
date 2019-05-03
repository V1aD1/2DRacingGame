#include "include/ParticlePhysicsComponent.h"
#include "include/Entity.h"
#include "include/MathCommon.h"

ParticlePhysicsComponent::ParticlePhysicsComponent() : 
	PhysicsComponent(sf::Vector2f(), 0, std::vector<sf::Vector2f>(), 0.3f, 180.0f, 0.5f, 0, 0, 150.0f)
{
}

ParticlePhysicsComponent::~ParticlePhysicsComponent()
{
}

void ParticlePhysicsComponent::Update(Entity& entity, float dtMilli)
{
	m_prevState = m_currState;
	m_newState.Update(dtMilli, particle_maxMomentum);
	m_currState = m_newState;
	
	entity.SetPosition(m_currState.GetWorldPosition());
	entity.SetRotation(MathCommon::RadiansToDegrees(m_currState.GetRotInRad()));
}

//not handling any collision on particles... FOR NOW
sf::Vector2f ParticlePhysicsComponent::HandleCollision(sf::Vector2f otherEntityMomentum)
{
	return sf::Vector2f(0,0);
}

//unnecessary functionality for particles
void ParticlePhysicsComponent::DBG_Slide(Entity& entity, const sf::Vector2f & dir, float dtMilli)
{
}

void ParticlePhysicsComponent::Brake(float dtTimeMilli)
{
}
