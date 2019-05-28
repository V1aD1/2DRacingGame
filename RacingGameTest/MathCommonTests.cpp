#include "stdafx.h"
#include "CppUnitTest.h"

#define M_PI       3.14159265358979323846   // pi

#include "../RacingGame/src/other/MathCommon.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RacingGameTest
{		
	TEST_CLASS(MathCommonTest)
	{
	public:
		
		TEST_METHOD(functionality_test)
		{
			auto result = MathCommon::CrossProduct(sf::Vector2f(-1, 1) - sf::Vector2f(1, 1), sf::Vector2f(1, 1) - sf::Vector2f(0, 0));
			auto result2 = MathCommon::CrossProduct(sf::Vector2f(-1, 1) - sf::Vector2f(1, 1), sf::Vector2f(1, 1) - sf::Vector2f(0, 10));
			auto result3 = MathCommon::CrossProduct(sf::Vector2f(-1, 1) - sf::Vector2f(1, 1), sf::Vector2f(1, 1) - sf::Vector2f(1, 1));
			auto result4 = MathCommon::CrossProduct(sf::Vector2f(-1, 1) - sf::Vector2f(1, 1), sf::Vector2f(1, 1) - sf::Vector2f(10, 1));
		}

		TEST_METHOD(rotate_test) {
			auto result = MathCommon::Rotate(sf::Vector2f(1, 0), MathCommon::DegreesToRadians(90.0f));
			auto result2 = MathCommon::Rotate(sf::Vector2f(1, 0), MathCommon::DegreesToRadians(45.0f));
			auto result3 = MathCommon::GetAngleBetweenVectorsInRads(sf::Vector2f(1, 0), sf::Vector2f(1, 1));
			auto result4 = MathCommon::GetAngleBetweenVectorsInRads(sf::Vector2f(1, 0), sf::Vector2f(1, -1));
		}

	};
}