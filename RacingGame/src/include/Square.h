#pragma once

#include <SFML/Graphics.hpp>

class Square
{
public:
	Square(float sideLen, sf::Vector2f position);
	~Square();

	sf::RectangleShape shape;

private: 
};

