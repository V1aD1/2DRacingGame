#pragma once
#include "Entity.h"


class ConvexEntity : public Entity
{

public:
	ConvexEntity();

	ConvexEntity(sf::Vector2f pos, float rot);
	ConvexEntity(sf::Vector2f pos, float rot, std::array<sf::Vector2f, 4> localCorners);

	~ConvexEntity();

	sf::Shape* const GetShape() const;
	void SetShape(sf::Shape* newShape);

	//This function receives corners in local space, sets them, then rotates them according to the 
	//rotation of the entity
	void SetCorners(const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied);
	std::array<sf::Vector2f, 4> GetWorldCorners() const;

	void Rotate(float newRotInDegrees);
	void SetPosition(sf::Vector2f newPos);

protected:
	sf::Shape* m_shape;

	//todo entire corners functionality can be replaced by sf::SHape.getPoint()...
	std::array<sf::Vector2f, 4> m_localCorners;

	//sets rotation and updates Shape and rotates corners as well
	void SetRotation(float degrees);
};

