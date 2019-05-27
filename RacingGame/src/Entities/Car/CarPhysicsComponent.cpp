#include <iostream>

#include "CarPhysicsComponent.h"
#include "../../Entities/Entity.h"
#include "../../Other/MathCommon.h"
#include "../Particle/ParticleEmitter.h"

const float CarPhysicsComponent::car_rotationSpeed = 180.0f;
const float CarPhysicsComponent::car_acceleration = 0.25f;
const float CarPhysicsComponent::car_frictionForce = 0.1f;
const float CarPhysicsComponent::car_brakeDeceleration = 0.1f;
const float CarPhysicsComponent::car_maxVel = 0.3f;
const float CarPhysicsComponent::car_skidEffectFrequencyMs = 200.0f;

ParticleEmitter G_EMITTER;

CarPhysicsComponent::CarPhysicsComponent(sf::Vector2f pos, float rotRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied) :
	PhysicsComponent(pos,
		rotRad,
		cornersWithoutRotationApplied,
		car_maxVel,
		car_rotationSpeed,
		car_acceleration,
		car_frictionForce)
{
	car_timeSinceLastSkidEffect = car_skidEffectFrequencyMs;
}


CarPhysicsComponent::~CarPhysicsComponent()
{
}

void CarPhysicsComponent::Update(Entity& entity, float dtMilli)
{
	m_prevState = m_currState;
	ApplyFriction(dtMilli);
	m_newState.Update(dtMilli, car_maxVel);

	auto collisionInfo = DetectCollision(entity);
	auto collisionEntity = std::get<0>(collisionInfo);
	auto collisionLocation = std::get<1>(collisionInfo);

	//update to new state only if NO collision occured
	if (collisionEntity == nullptr) { m_currState = m_newState; }

	//if collision occurs then halt all velocity on the car
	//and do NOT apply new state
	else {

		//alert other entity of collision
		auto absorbedVel = collisionEntity->HandleCollision(m_newState.GetVelocity());

		//emit collision spark
		G_EMITTER.EmitCone(
			collisionLocation,
			-absorbedVel,
			0.2f,
			0.2f,
			-3.0f,
			0.5f,
			-2.0f,
			60,
			MathCommon::GetMagnitude(absorbedVel) / car_maxVel * 5,
			10);

		m_currState.SetVelocity(m_newState.GetVelocity() - absorbedVel);
		m_currState.SetCurrentAcceleration(0);
		m_newState = m_currState;
	}

	//skidding effect 
	if (m_currState.GetCurrentAcceleration() != 0 && MathCommon::GetMagnitude(m_currState.GetVelocity()) < m_maxSpeed / 2) {
		CreateDustClouds(entity, { 0, 3 });
	}

	car_timeSinceLastSkidEffect += dtMilli;

	PhysicsComponent::Update(entity, dtMilli);
}

void CarPhysicsComponent::Brake(Entity& entity, float dtTimeMilli)
{
	m_braking_flag = true;
	SlowDown(car_brakeDeceleration, dtTimeMilli);
	CreateDustClouds(entity, { 0,1,2,3 });
}

void CarPhysicsComponent::DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli)
{
	//halting all movement on the car
	m_newState.SetVelocity(sf::Vector2f(0.0f, 0.0f));
	m_newState.SetWorldPos(m_newState.GetWorldPosition() + dir * dtMilli / 1000.0f * m_dbg_slideSpeed);
	m_newState.Update(dtMilli, car_maxVel);
}

sf::Vector2f CarPhysicsComponent::HandleCollision(sf::Vector2f otherEntityVel)
{
	auto absorbedVel = otherEntityVel / 2.0f;
	m_newState.ApplyVelocity(absorbedVel);
	return absorbedVel;
}

void CarPhysicsComponent::Rotate(float dtTimeMilli, bool left)
{
	int direction = left ? -1 : 1;

	float rotAmount = 0;

	auto newStateSpeed = MathCommon::GetMagnitude(m_newState.GetVelocity());

	//no turning if car isn't moving
	if (newStateSpeed > 0.0f) {
		//accelerating
		//so slow turn, always move in direction facing
		if (m_newState.GetCurrentAcceleration() != 0.0f) {
			auto rotSlowDownFactor = 2.0f * newStateSpeed / m_maxSpeed;

			if (rotSlowDownFactor < 1.0f)
				rotSlowDownFactor = 1.0f;

			rotAmount = direction * (m_rotationSpeed / rotSlowDownFactor) * (dtTimeMilli / 1000.0f);
			m_newState.Rotate(MathCommon::DegreesToRadians(rotAmount));
			SetVelocityToFaceCurrDirection(newStateSpeed);
		}

		//braking, but not accelerating, so drifting
		//really fast turn, velocity slowly turning towards direction facing
		//this is done in order to simulate drifting
		else if (m_braking_flag) {
			rotAmount = direction * m_rotationSpeed * (dtTimeMilli / 1000.0f);
			m_newState.Rotate(MathCommon::DegreesToRadians(rotAmount));
		}

		//neither
		//normal speed turn, always move in direction facing
		else {
			auto rotSlowDownFactor = 1.5f * newStateSpeed / m_maxSpeed;

			if (rotSlowDownFactor < 1.0f)
				rotSlowDownFactor = 1.0f;

			rotAmount = direction * (m_rotationSpeed / rotSlowDownFactor) * (dtTimeMilli / 1000.0f);
			m_newState.Rotate(MathCommon::DegreesToRadians(rotAmount));
			SetVelocityToFaceCurrDirection(newStateSpeed);
		}
	}
}

void CarPhysicsComponent::SetBrakingFlag(bool newFlag)
{
	m_braking_flag = newFlag;
}

void CarPhysicsComponent::CreateDustClouds(Entity& entity, std::vector<int> wheels)
{
	if (car_timeSinceLastSkidEffect > car_skidEffectFrequencyMs && m_currState.GetVelocity() != sf::Vector2f(0,0)) {
		auto wheelPositions = entity.GetWorldCorners();

		for (auto wheel : wheels) {
			G_EMITTER.EmitCircle(wheelPositions->at(wheel), 0, 0, 0, 1.0f, 2.0f, 1, 0);
		}
		car_timeSinceLastSkidEffect = 0;
	}
}

void CarPhysicsComponent::SetVelocityToFaceCurrDirection(float speed)
{
	m_newState.SetVelocity(MathCommon::ChangeLength(m_newState.GetForwardDir(), speed));
}
