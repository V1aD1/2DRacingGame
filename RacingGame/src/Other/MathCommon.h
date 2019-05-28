#pragma once
#include <SFML/Graphics.hpp>

class MathCommon
{
public:
	static float DegreesToRadians(float deg);
	static float RadiansToDegrees(float rad);
	static float GetMagnitude(const sf::Vector2f& vec);
	static sf::Vector2f ChangeLength(const sf::Vector2f& vec, float newLen);
	static sf::Vector2f Normalize(const sf::Vector2f& vec);
	static float CrossProduct(const sf::Vector2f& a, const sf::Vector2f& b);
	static float Multiply(const sf::Vector2f& a, const sf::Vector2f& b);
	static sf::Vector2f Subtract(const sf::Vector2f& a, const sf::Vector2f& b);
	static float GetAngleBetweenVectorsInRads(const sf::Vector2f& a, const sf::Vector2f& b);
	static bool CheckLineCollision(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& q1, const sf::Vector2f& q2);
	static bool AreColliding(const std::vector<sf::Vector2f>& firstShapeCorners, const std::vector<sf::Vector2f>& secondShapeCorners);
	static sf::Vector2f Rotate(const sf::Vector2f& vec, float rads);

private:
	///returns 0 if points are clockwise, 1 if counter clockwise, and 2 if collinear
	static int GetOrientation(const sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3);
};


