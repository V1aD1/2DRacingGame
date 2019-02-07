#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Entity.h"

class Square : public Entity
{
public:

	Square(float sideLen, sf::Vector2f position, float rotation);
	~Square();

	void Update(sf::RenderWindow& window, float dtTimeMilli);

private: 
	float sideLength;
};

