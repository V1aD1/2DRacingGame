#pragma once
#include <SFML/Graphics.hpp>

class MathCommon
{
public:
	static float DegreesToRadians(float deg);
	static float GetMagnitude(sf::Vector2f vec);
	static sf::Vector2f ChangeLength(const sf::Vector2f& vec, float newLen);
	static sf::Vector2f Normalize(const sf::Vector2f& vec);
	static bool CheckIntersection(const sf::Vector2f& a1, const sf::Vector2f & a2, const sf::Vector2f& b1, const sf::Vector2f& b2);
	static float CrossProduct(const sf::Vector2f& a, const sf::Vector2f& b);

private:
	///returns 0 if points are clockwise, 1 if counter clockwise, and 2 if collinear
	static int GetOrientation(const sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3);
};


