#pragma once
#include "../../Components/PhysicsComponent.h"

class TerrainPhysicsComponent : public PhysicsComponent
{
private:
	float m_frictionCoefficient;
	float m_newMaxSpeed;

public:
	TerrainPhysicsComponent(sf::Vector2f pos, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied, float frictionCoefficient, float newMaxSpeed);
	~TerrainPhysicsComponent();

	sf::Vector2f HandleCollision(sf::Vector2f otherEntityVel, Entity& otherEntity) override;
};

