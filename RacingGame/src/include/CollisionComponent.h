#pragma once

class CollisionComponent
{
private:
	//todo make to variable corner length
	std::array<sf::Vector2f, 4> m_localCorners;
	std::array<sf::Vector2f, 4> m_worldCorners;


public:
	CollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied);
	~CollisionComponent();

	CollisionComponent& operator=(const CollisionComponent& other);

	void Update(sf::Vector2f newPos, float newRotInRad);
	const std::array<sf::Vector2f, 4>& GetWorldCorners() const;
};

