#pragma once
#include "PhysicsComponent.h"

class CarPhysicsComponent :public PhysicsComponent
{
public:
	static const float car_rotationSpeed;
	static const float car_acceleration;
	static const float car_brakeForce;
	static const float car_frictionForce;
	static const float car_dbg_slideSpeed;
	static const float car_maxMomentum;

public:
	CarPhysicsComponent(sf::Vector2f pos, float rotRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied);
	~CarPhysicsComponent();

	void Update(Entity& entity, float dtMilli) override;
	void Brake(float dtTimeMilli) override;
	void DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli) override;
	virtual sf::Vector2f HandleCollision(sf::Vector2f otherEntityMomentum) override;

};

