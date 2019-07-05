#pragma once
#include "../../Components/PhysicsComponent.h"

class TerrainPhysicsComponent : public PhysicsComponent
{
private:
	float m_frictionCoefficient;

public:
	TerrainPhysicsComponent(sf::Vector2f pos, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied, float frictionCoefficient);
	~TerrainPhysicsComponent();

	sf::Vector2f HandleCollision(sf::Vector2f otherEntityVel, Entity& otherEntity) override;
};

