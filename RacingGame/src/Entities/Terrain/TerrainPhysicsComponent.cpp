#include "TerrainPhysicsComponent.h"



TerrainPhysicsComponent::TerrainPhysicsComponent(sf::Vector2f pos, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied) : 
	PhysicsComponent(pos, 0, cornersWithoutRotationApplied, 0, 0, 0, 0)
{
}


TerrainPhysicsComponent::~TerrainPhysicsComponent()
{
}

sf::Vector2f TerrainPhysicsComponent::HandleCollision(sf::Vector2f otherEntityVel)
{
	//change the friction coeficient of the entity here

	return sf::Vector2f();
}
