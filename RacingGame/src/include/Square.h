#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "ConvexEntity.h"

class Square : virtual public Entity
{
public:

	Square(float sideLen, sf::Vector2f position, float rotation);
	~Square();

private: 
	float sideLength;
};

