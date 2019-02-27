#pragma once

class Entity;

class CollisionComponent
{
private:
	std::array<sf::Vector2f, 4> m_localCorners;
	std::array<sf::Vector2f, 4> m_worldCorners;


public:
	CollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied);
	~CollisionComponent();

	void Update(sf::Vector2f newPos, float newRotInRad);
	const std::array<sf::Vector2f, 4>* GetWorldCorners() const;
};

