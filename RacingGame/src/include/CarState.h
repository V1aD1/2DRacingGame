#pragma once
#include "c:\SFML Projects\RacingGame\RacingGame\src\include\ConvexEntity.h"
class CarState : public ConvexEntity{
public:
	sf::Vector2f forwardDir = sf::Vector2f(1.0f, 0.0f);
	sf::Vector2f momentum = sf::Vector2f(0.0f, 0.0f);

public:
	~CarState();

	CarState(sf::Vector2f pos, float rot, sf::Vector2f size);
	void UpdateToNewState(const CarState& newState);
	void ApplyFriction(float fricForce, float dtTimeMilli);
	void ApplySlowDownForce(float forceMag, float dtTimeMilli);
};

