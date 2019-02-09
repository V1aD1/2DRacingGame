#include <array>
#include <SFML/Graphics.hpp>

#pragma once
class Entity
{
public:
	Entity();
	Entity(sf::Vector2f position, float rot);
	~Entity();

	sf::Vector2f GetPosition() const;
	float GetRotation() const;
	
	void SetPosition(sf::Vector2f newPos);

protected:
	sf::Vector2f m_position;
	float m_rotation;
	float m_rotationInRad;

	void SetRotation(float degrees);
};

