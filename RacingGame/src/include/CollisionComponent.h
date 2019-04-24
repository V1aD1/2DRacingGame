#pragma once
#include <SFML/Graphics.hpp>

class CollisionComponent
{
private:
	std::vector<sf::Vector2f> m_localCorners;
	std::vector<sf::Vector2f> m_worldCorners;

public:
	CollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied);
	~CollisionComponent();

	virtual CollisionComponent& operator=(const CollisionComponent& other);

	virtual void Update(sf::Vector2f newPos, float newRotInRad);
	virtual const std::vector<sf::Vector2f>& GetWorldCorners() const;
};

