#pragma once
#include "../../Components/PhysicsComponent.h"

class TerrainPhysicsComponent : public PhysicsComponent
{
public:
	TerrainPhysicsComponent(sf::Vector2f pos, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied);
	~TerrainPhysicsComponent();

	sf::Vector2f HandleCollision(sf::Vector2f otherEntityVel) override;
};

