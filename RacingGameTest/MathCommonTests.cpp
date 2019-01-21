#include "stdafx.h"
#include "CppUnitTest.h"

#define M_PI       3.14159265358979323846   // pi

#include "../RacingGame/src/MathCommon.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RacingGameTest
{		
	TEST_CLASS(MathCommonTest)
	{
	public:
		
		TEST_METHOD(Test_line_intersection)
		{
			Assert::AreEqual(MathCommon::CheckIntersection(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(4.0f, 4.0f), sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 4.0f)), true);
		}

	};
}