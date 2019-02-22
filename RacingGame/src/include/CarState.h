#pragma once
#include "PhysicsEntity.h"


class CarState : public PhysicsEntity{
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

