#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Entity.h"

class Square : public Entity
{
public:

	Square(float sideLen, sf::Vector2f position, float rotation);
	~Square();

	virtual const std::array<sf::Vector2f, 4>* GetWorldCorners() const;

private: 
	float sideLength;
	std::array<sf::Vector2f, 4> m_worldCorners;
};

