#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "MathCommon.h"



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

bool MathCommon::CheckLineCollision(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2)
{
	//as per https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
	//vectors will be represented by a start point (p, q) and end point (p+r, q+s),
	//where r or s = endpoint - startpoint

	auto r = p2 - p1;
	auto s = q2 - q1;

	//you'll be comparing vectors connecting every corner to the next,
	//around the shape, with the 4 sides of each cell that shape may be within
	//vectors are p + r and q + s
	//t = (q - p) x s / (r x s)
	//u = (q - p) x r/(r x s)
	//NOTE: (q - p) and (r x s) used in both equations,
	//so only compute them once!!

	auto QMinP = q1 - p1;
	auto RCrossS = MathCommon::CrossProduct(r, s);

	//Collinear: if r x s = 0 AND (q - p) x r = 0 (we care)
	if (RCrossS == 0.0f && MathCommon::CrossProduct(QMinP, r) == 0) {
		return true;
	}

	//Intersection: if r x s != 0 and 0 <= t <= 1 and 0 <= u <= 1
	else if (RCrossS != 0.0f) {
		auto t = MathCommon::CrossProduct(QMinP, s) / RCrossS;
		auto u = MathCommon::CrossProduct(QMinP, r) / RCrossS;

		if (0.0f <= t && t <= 1.0f && 0.0f <= u && u <= 1.0f)
		{
			return true;
		}
	}

	//Parallel, non intersecting: r  x s = 0 and (q - p) x r != 0 (don't care)

	//Else, lines are not parallel BUT do NOT intersect (don't care)

	return false;
}

bool MathCommon::AreColliding(std::vector<sf::Vector2f> firstShapeCorners, std::vector<sf::Vector2f> secondShapeCorners)
{
	//line intersection test
	for (int i = 0; i < firstShapeCorners.size(); i++) {
		auto firstShapeCurrCorner = firstShapeCorners[i];
		auto firstShapeNextCorner = (i == (firstShapeCorners.size() - 1)) ? firstShapeCorners[0] : firstShapeCorners[i + 1];

		for (int i = 0; i < secondShapeCorners.size(); i++) {
			auto secondShapeCurrCorner = secondShapeCorners[i];
			auto secondShapeNextCorner = (i == (secondShapeCorners.size() - 1)) ? secondShapeCorners[0] : secondShapeCorners[i + 1];

			if (MathCommon::CheckLineCollision(firstShapeCurrCorner,
				firstShapeNextCorner,
				secondShapeCurrCorner,
				secondShapeNextCorner) == true)
			{
				return true;
			}

		}
	}
	return false;
}

