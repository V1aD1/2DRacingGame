#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "include/MathCommon.h"



float MathCommon::DegreesToRadians(float deg)
{
	return (deg * M_PI) / 180.0f;
}

float MathCommon::RadiansToDegrees(float rad)
{
	return (rad * 180.0f) / M_PI;
}

float MathCommon::GetMagnitude(const sf::Vector2f& vec) {
	return powf(powf(vec.x, 2) + powf(vec.y, 2), 0.5);
}

sf::Vector2f MathCommon::ChangeLength(const sf::Vector2f& vec, float newLen)
{
	return vec * newLen / GetMagnitude(vec);
}

sf::Vector2f MathCommon::Normalize(const sf::Vector2f& vec)
{
	return vec / GetMagnitude(vec);
}

float MathCommon::CrossProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return (a.x * b.y) - (a.y * b.x);
}

float MathCommon::Multiply(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

sf::Vector2f MathCommon::Subtract(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sf::Vector2f(a.x - b.x, a.y - b.y);
}

float MathCommon::GetAngleBetweenVectorsInRads(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return acos(Multiply(Normalize(a), Normalize(b)));
}

int MathCommon::GetOrientation(const sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3)
{
	return 0;
}
