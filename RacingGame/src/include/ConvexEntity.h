#pragma once
#include "Entity.h"
#include "GraphicsComponent.h"

class ConvexEntity : public Entity
{

public:
	ConvexEntity();
	ConvexEntity(sf::Vector2f pos, float rot);
	ConvexEntity(sf::Vector2f pos, float rot, std::array<sf::Vector2f, 4> localCorners);
	~ConvexEntity();

	sf::Shape* const GetShape() const;
	std::array<sf::Vector2f, 4> GetWorldCorners() const;
	
	//This function receives corners in local space, sets them, then rotates them according to the 
	//rotation of the entity
	void SetCorners(const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied);
	void SetShape(sf::Shape* newShape);
	void SetPosition(sf::Vector2f newPos);

	void Rotate(float newRotInDegrees);
	void Update(sf::RenderWindow & window, float dtTimeMilli);

protected:
	sf::Shape* m_shape;
	std::array<sf::Vector2f, 4> m_localCorners;

protected:
	//sets rotation and updates Shape and rotates corners as well
	void SetRotation(float degrees);

private:
	GraphicsComponent* m_graphics;
};

