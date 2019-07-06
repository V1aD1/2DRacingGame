#include "TerrainPhysicsComponent.h"
#include "../Entity.h"

TerrainPhysicsComponent::TerrainPhysicsComponent(sf::Vector2f pos, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied, float frictionCoefficient, float newMaxSpeed) :
	PhysicsComponent(pos, 0, cornersWithoutRotationApplied, 0, 0, 0, 0)
{
	m_frictionCoefficient = frictionCoefficient;
	m_newMaxSpeed = newMaxSpeed;
}


TerrainPhysicsComponent::~TerrainPhysicsComponent()
{
}

sf::Vector2f TerrainPhysicsComponent::HandleCollision(sf::Vector2f otherEntityVel, Entity& otherEntity)
{
	//change the friction coeficient of the entity here
	if (otherEntity.m_physics)
	{
		otherEntity.m_physics->AddToCurrFriction(m_frictionCoefficient);
		otherEntity.m_physics->SetMaxSpeed(m_newMaxSpeed);
	}

	return sf::Vector2f();
}
