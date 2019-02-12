#include <array>
#include <SFML/Graphics.hpp>

#pragma once
class Entity
{

//todo make private since rotation should only be changeable through SetRotation()
protected:
	sf::Vector2f m_position;
	float m_rotation;
	float m_rotationInRad;

public:
	Entity();

	sf::Vector2f GetPosition() const;
	float GetRotationInDegrees() const;
	float GetRotationInRadians() const;


	void SetPosition(sf::Vector2f newPos);

	~Entity();

protected:
	Entity(sf::Vector2f position, float rot);

	//sets both the m_rotation and m_rotationInRad
	void SetRotation(float degrees);
};

