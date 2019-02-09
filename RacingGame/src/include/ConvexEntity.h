#pragma once
#include "Entity.h"


class ConvexEntity : public Entity
{

public:
	ConvexEntity();

	ConvexEntity(sf::Vector2f pos, float rot);

	~ConvexEntity();

	sf::Shape* const GetShape() const;
	void SetShape(sf::Shape* newShape);

	void SetCorners(const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied);
	std::array<sf::Vector2f, 4> GetWorldCorners() const;


	void Rotate(float newRotInDegrees);

private:
	sf::Shape* m_shape;
	std::array<sf::Vector2f, 4> m_localCorners;

	void SetRotation(float degrees);
};

