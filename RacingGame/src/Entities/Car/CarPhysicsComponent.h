#pragma once
#include "../../Components/PhysicsComponent.h"

class CarPhysicsComponent :public PhysicsComponent
{
private:
	static const float car_rotationSpeed;
	static const float car_acceleration;
	static const float car_frictionForce;
	static const float car_brakeDeceleration;
	static const float car_dbg_slideSpeed;
	static const float car_maxVel;
	static const float car_skidEffectFrequencyMs;

	//flags
	//todo read up on flags...
	bool m_braking_flag;
	bool m_reversing_flag;

private:
	float car_timeSinceLastSkidEffect;

public:
	CarPhysicsComponent(sf::Vector2f pos, float rotRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied);
	~CarPhysicsComponent();

	void Update(Entity& entity, float dtMilli) override;
	void Brake(Entity& entity, float dtTimeMilli) override;
	void DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli) override;
	sf::Vector2f HandleCollision(sf::Vector2f otherEntityVel) override;
	void Rotate(float dtTimeMilli, bool left) override;
	void SetBrakingFlag(bool newFlag) override;
	void SetReversingFlag(bool newFlag) override;

private:
	void CreateDustClouds(Entity& entity, std::vector<int> wheels);
	void AllignVelocityWithNewDir(float dtTimeMilli, sf::Vector2f dirToAllignTo);
};

