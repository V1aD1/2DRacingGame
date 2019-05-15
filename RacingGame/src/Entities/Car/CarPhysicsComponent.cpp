#include "CarPhysicsComponent.h"
#include "../../Entities/Entity.h"
#include "../../Other/MathCommon.h"
#include "../Particle/ParticleEmitter.h"

//todo shouldn't these be private members of CarPhysicsComponent??
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

	auto collisionInfo = CollisionDetected(entity);
	auto collisionEntity = std::get<0>(collisionInfo);
	auto collisionLocation = std::get<1>(collisionInfo);

	//update to new state only if NO collision occured
	if (collisionEntity == nullptr) { m_currState = m_newState; }

	//if collision occurs then halt all velocity on the car
	//and do NOT apply new state
	else {

		//alert other entity of collision
		auto absorbedVel = collisionEntity->HandleCollision(m_newState.GetVelocity());

		G_EMITTER.EmitCone(
			collisionLocation,
			-absorbedVel,
			0.2f,
			-3.0f,
			-2.0f,
			-2.0f,
			60,
			MathCommon::GetMagnitude(absorbedVel) / car_maxVel * 5);

		m_currState.SetVelocity(m_newState.GetVelocity() - absorbedVel);
		m_currState.SetAcceleration(0);
		m_newState = m_currState;
	}

	//skidding effect 
	if (m_currState.GetAcceleration() != 0 && MathCommon::GetMagnitude(m_currState.GetVelocity()) < m_maxSpeed / 2) {
		CreateDustClouds(entity, { 0, 3 });
	}

	//todo this should be in the PhysicsComponent.Update() function
	entity.SetPosition(m_currState.GetWorldPosition());
	entity.SetRotation(MathCommon::RadiansToDegrees(m_currState.GetRotInRad()));

	//todo don't like doing this here, should be done somewhere else, automatically?
	m_newState.SetAcceleration(0);

	car_timeSinceLastSkidEffect += dtMilli;
}

void CarPhysicsComponent::Brake(Entity& entity, float dtTimeMilli)
{
	//todo add dus effect for braking if car moving

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

void CarPhysicsComponent::CreateDustClouds(Entity& entity, std::vector<int> wheels)
{
	if (car_timeSinceLastSkidEffect > car_skidEffectFrequencyMs) {
		auto wheelPositions = entity.GetWorldCorners();

		for (auto wheel : wheels) {
			G_EMITTER.EmitCircle(wheelPositions->at(wheel), 0, 0, -0.05f, 2.0f, 1);
		}
		car_timeSinceLastSkidEffect = 0;
	}
}
