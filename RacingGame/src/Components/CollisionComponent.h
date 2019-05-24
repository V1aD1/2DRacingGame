#pragma once
#include <SFML/Graphics.hpp>

class CollisionComponent
{
protected:
	std::vector<sf::Vector2f> m_localCorners;
	std::vector<sf::Vector2f> m_worldCorners;

public:
	CollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied);
	~CollisionComponent();

	CollisionComponent& operator=(const CollisionComponent& other);
	const std::vector<sf::Vector2f>& GetWorldCorners() const;
	std::tuple<bool, sf::Vector2f> IsColliding(const std::vector<sf::Vector2f>* otherEntityWorldCornersPtr) const;

	virtual void Update(sf::Vector2f newPos, float newRotInRad) = 0;
};

