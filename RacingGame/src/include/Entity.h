#include <array>
#include <SFML/Graphics.hpp>

#pragma once
class Entity
{
public:
	Entity(sf::Vector2f position, float rot);
	~Entity();

	sf::Vector2f GetPosition() const;
	float GetRotation() const;
	
	std::array<sf::Vector2f, 4> GetWorldCorners() const;
	sf::Shape* const GetShape() const;

protected:
	sf::Vector2f m_position;
	float m_rotation;

	std::array<sf::Vector2f, 4> m_localCorners;
	sf::Shape* m_shape;
};

