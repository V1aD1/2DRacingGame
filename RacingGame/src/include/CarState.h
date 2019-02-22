#pragma once
#include "PhysicsEntity.h"


class CarState{
public:
	sf::Vector2f forwardDir = sf::Vector2f(1.0f, 0.0f);
	sf::Vector2f momentum = sf::Vector2f(0.0f, 0.0f);
	std::array<sf::Vector2f, 4> m_localCorners;
public:
	~CarState();

	CarState(std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied);
	void UpdateToNewState(const CarState& newState);
};

