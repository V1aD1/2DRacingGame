#include <iostream>

#include "CarPhysicsComponent.h"
#include "../../Entities/Entity.h"
#include "../../Other/MathCommon.h"
#include "../Particle/ParticleEmitter.h"

//todo make rot speed be based on speed and whether braking
const float CarPhysicsComponent::car_rotationSpeed = 180.0f;
const float CarPhysicsComponent::car_acceleration = 0.25f;
const float CarPhysicsComponent::car_frictionForce = 0.1f;
const float CarPhysicsComponent::car_brakeDeceleration = 0.1f;
const float CarPhysicsComponent::car_maxSpeed = 0.3f;
const float CarPhysicsComponent::car_skidEffectFrequencyMs = 200.0f;

ParticleEmitter G_EMITTER;

CarPhysicsComponent::CarPhysicsComponent(sf::Vector2f pos, float rotRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied) :
	PhysicsComponent(pos,
		rotRad,
		cornersWithoutRotationApplied,
		car_maxSpeed,
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

	//resetting the value of the current friction, 
	//so that it resets to default if leaving a terrain
	m_currFrictionDeceleration = m_frictionDeceleration;

	//determining if moving forward or backward
	bool movingForward = false, movingBackward = false;
	if (MathCommon::GetMagnitude(m_newState.GetVelocity()) > 0) {
		
		auto angleVelAndDir = MathCommon::RadiansToDegrees(MathCommon::GetAngleBetweenVectorsInRads(m_newState.GetVelocity(), m_newState.GetForwardDir()));

		if (angleVelAndDir < 65 && angleVelAndDir > -65)
			movingForward = true;

		else if (abs(angleVelAndDir) > 135)
			movingBackward = true;
	}

	//if braking, car will skid, in order to simulate drifting
	if (!m_braking_flag)
	{
		if (movingForward)
			AllignVelocityWithNewDir(dtMilli, m_newState.GetForwardDir());
		else if(movingBackward)
			AllignVelocityWithNewDir(dtMilli, -m_newState.GetForwardDir());
		//if moving perpendicularly then don't realign velocity
	}

	m_newState.Update(dtMilli, m_maxSpeed);
	m_maxSpeed = car_maxSpeed;

	auto collisionInfo = DetectCollision(entity);
	auto collisionEntity = std::get<0>(collisionInfo);
	auto collisionLocation = std::get<1>(collisionInfo);

	if(collisionEntity != nullptr){

		//alert other entity of collision
		auto absorbedVel = collisionEntity->HandleCollision(m_newState.GetVelocity(), entity);

		//if collision occurs with a kinematic object 
		//then halt all velocity on the car and do NOT apply new state
		//otherwise apply new state
		if (MathCommon::GetMagnitude(absorbedVel) > 0.0f) {
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
				MathCommon::GetMagnitude(absorbedVel) / car_maxSpeed * 5,
				10);

			//this is necessary to make the car recover from a collision more quickly...
			m_newState = m_currState;
			m_newState.SetVelocity(m_newState.GetVelocity() - absorbedVel);
		}
	}

	m_currState = m_newState;

	//skidding effect 
	if (m_currState.GetCurrentAcceleration() != 0 && MathCommon::GetMagnitude(m_currState.GetVelocity()) < m_maxSpeed / 2) {
		CreateDustClouds(entity, { 2, 3 });
	}

	else if (abs(MathCommon::RadiansToDegrees(MathCommon::GetAngleBetweenVectorsInRads(m_currState.GetForwardDir(), m_currState.GetVelocity()))) > 45.0f){
		CreateDustClouds(entity, { 0, 1, 2, 3 });
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
	m_newState.Update(dtMilli, car_maxSpeed);
}

sf::Vector2f CarPhysicsComponent::HandleCollision(sf::Vector2f otherEntityVel, Entity& otherEntity)
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

		rotAmount = direction * m_rotationSpeed * (dtTimeMilli / 1000.0f);
		m_newState.Rotate(MathCommon::DegreesToRadians(rotAmount));
	}
}

void CarPhysicsComponent::SetBrakingFlag(bool newFlag)
{
	m_braking_flag = newFlag;
}

void CarPhysicsComponent::SetReversingFlag(bool newFlag)
{
	m_reversing_flag = newFlag;
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

void CarPhysicsComponent::AllignVelocityWithNewDir(float dtTimeMilli, sf::Vector2f dirToAllignTo)
{
	if (MathCommon::GetMagnitude(m_newState.GetVelocity()) == 0.0f)
		return;

	auto angle = MathCommon::RadiansToDegrees(MathCommon::GetAngleBetweenVectorsInRads(dirToAllignTo, m_newState.GetVelocity()));
	float correctionAngle = (car_rotationSpeed / 3.0f) *(dtTimeMilli / 1000.0f);

	if (abs(angle) < abs(correctionAngle))
		correctionAngle = angle;

	if (angle < 0.0f)
		correctionAngle = -correctionAngle;

	sf::Vector2f newSpeedDir = MathCommon::Rotate(m_newState.GetVelocity(), MathCommon::DegreesToRadians(correctionAngle));

	m_newState.SetVelocity(MathCommon::ChangeLength(newSpeedDir, MathCommon::GetMagnitude(m_newState.GetVelocity())));
}
