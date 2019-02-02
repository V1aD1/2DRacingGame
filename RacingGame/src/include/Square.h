#pragma once

#include <array>
#include <SFML/Graphics.hpp>

class Square
{
public:

	Square(float sideLen, sf::Vector2f position, float rotation);
	~Square();

	void Update(sf::RenderWindow& window, float dtTimeMilli);

	std::array<sf::Vector2f, 4> GetCorners();
	std::array<bool, 4> GetCollisionChecks();

private: 
	sf::RectangleShape shape;
	std::array<sf::Vector2f, 4> corners;
    std::array<bool, 4> collisionChecks;
	float sideLength;
	float rotation;
	sf::Vector2f position;
};

