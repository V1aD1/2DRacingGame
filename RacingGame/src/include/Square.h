#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "ConvexEntity.h"

class Square : public ConvexEntity
{
public:

	Square(float sideLen, sf::Vector2f position, float rotation);
	~Square();

	void Update(sf::RenderWindow& window, float dtTimeMilli);

private: 
	float sideLength;
};

