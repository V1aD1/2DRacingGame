#define _USE_MATH_DEFINES
#include <cmath>

#include "include/MathCommon.h"


float MathCommon::DegreesToRadians(float deg)
{
	return (deg * M_PI) / 180.0f;
}

float MathCommon::GetMagnitude(sf::Vector2f vec) {
	return powf(powf(vec.x, 2) + powf(vec.y, 2), 0.5);
}

sf::Vector2f MathCommon::ChangeLength(const sf::Vector2f & vec, float newLen)
{
	return vec * newLen / GetMagnitude(vec);
}

sf::Vector2f MathCommon::Normalize(const sf::Vector2f & vec)
{
	return vec / GetMagnitude(vec);
}

bool MathCommon::CheckIntersection(const sf::Vector2f& a1, const sf::Vector2f & a2, const sf::Vector2f& b1, const sf::Vector2f& b2)
{
	return false;
}

int MathCommon::GetOrientation(const sf::Vector2f & p1, sf::Vector2f & p2, sf::Vector2f & p3)
{
	return 0;
}
