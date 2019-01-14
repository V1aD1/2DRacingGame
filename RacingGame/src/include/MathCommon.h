#pragma once
#include <SFML/Graphics.hpp>

class MathCommon
{
public:
	static float DegreesToRadians(float deg);
	static float GetMagnitude(sf::Vector2f vec);
	static sf::Vector2f ChangeLength(const sf::Vector2f& vec, float newLen);
};


