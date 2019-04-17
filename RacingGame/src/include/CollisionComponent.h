#pragma once

class CollisionComponent
{
private:
	//todo make to variable corner length
	std::vector<sf::Vector2f> m_localCorners;
	std::vector<sf::Vector2f> m_worldCorners;

public:
	CollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied);
	~CollisionComponent();

	CollisionComponent& operator=(const CollisionComponent& other);

	void Update(sf::Vector2f newPos, float newRotInRad);
	const std::vector<sf::Vector2f>& GetWorldCorners() const;
};

