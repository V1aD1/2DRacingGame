#pragma once
#include "CollisionComponent.h"
class StaticCollisionComponent : public CollisionComponent
{
public:
	StaticCollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied);
	~StaticCollisionComponent();

	//StaticCollisionComponent& operator=(const StaticCollisionComponent& other) override;

	void Update(sf::Vector2f newPos, float newRotInRad) override;
	//const std::vector<sf::Vector2f>& GetWorldCorners() const override;
};

