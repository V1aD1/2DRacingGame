#define _USE_MATH_DEFINES
#include <cmath>

#include "include/MathCommon.h"


float MathCommon::DegreesToRadians(float deg)
{
	return (deg * M_PI) / 180.0f;
}

float MathCommon::GetMagnitude(sf::Vector2f vec) {
	return powf(pow(vec.x, 2) + pow(vec.y, 2), 0.5);
}

sf::Vector2f MathCommon::ChangeLength(const sf::Vector2f & vec, float newLen)
{
	return vec * newLen / GetMagnitude(vec);
}
