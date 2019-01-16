#pragma once

#include <SFML/Graphics.hpp>

class Square
{
public:
	Square(float sideLen, sf::Vector2f position, float rotation);

	void Update(sf::RenderWindow& window, float dtTimeMilli);

	~Square();

private: 
	sf::RectangleShape shape;
	sf::Vector2f points[4];
	float sideLength;
	float rotation;
	sf::Vector2f position;
};

