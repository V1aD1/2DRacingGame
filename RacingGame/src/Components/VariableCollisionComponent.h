#pragma once
#include "CollisionComponent.h"
class VariableCollisionComponent :
	public CollisionComponent
{
public:
	VariableCollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied);
	~VariableCollisionComponent();

	virtual void Update(sf::Vector2f newPos, float newRotInRad) override;
};

