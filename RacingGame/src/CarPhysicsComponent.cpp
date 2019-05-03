#include "include/CarPhysicsComponent.h"
#include "include/Entity.h"
#include "include/MathCommon.h"
#include "include/ParticleEmitter.h"

//todo shouldn't these be private members of CarPhysicsComponent??
const float CarPhysicsComponent::car_rotationSpeed = 180.0f;
const float CarPhysicsComponent::car_acceleration = 0.25f;
const float CarPhysicsComponent::car_brakeForce = 0.1f;
const float CarPhysicsComponent::car_frictionForce = 0.1f;
const float CarPhysicsComponent::car_dbg_slideSpeed = 150.0f;
const float CarPhysicsComponent::car_maxMomentum = 0.3f;

ParticleEmitter G_EMITTER;

CarPhysicsComponent::CarPhysicsComponent(sf::Vector2f pos, float rotRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied) :
	PhysicsComponent(pos,
		rotRad,
		cornersWithoutRotationApplied,
		car_maxMomentum,
		car_rotationSpeed,
		car_acceleration,
		car_brakeForce,
		car_frictionForce,
		car_dbg_slideSpeed)
{
}


CarPhysicsComponent::~CarPhysicsComponent()
{
}

void CarPhysicsComponent::Update(Entity& entity, float dtMilli)
{
	m_prevState = m_currState;
	ApplyFriction(dtMilli);
	m_newState.Update(dtMilli, car_maxMomentum);

	auto collisionInfo = CollisionDetected(entity);
	auto collisionEntity = std::get<0>(collisionInfo);
	auto collisionLocation = std::get<1>(collisionInfo);

	//update to new state only if NO collision occured
	if (collisionEntity == nullptr) { m_currState = m_newState; }

	//if collision occurs then halt all momentum on the car
	//and do NOT apply new state
	else {

		//alert other entity of collision
		auto absorbedMomentum = collisionEntity->HandleCollision(m_newState.GetMomentum());
		
		G_EMITTER.EmitCone(
			collisionLocation,
			//should only the y be flipped?
			absorbedMomentum,
			10,
			MathCommon::GetMagnitude(absorbedMomentum) / car_maxMomentum * 10);

			m_currState.SetMomentum(m_newState.GetMomentum() - absorbedMomentum);
			m_newState = m_currState;
	}

	//todo this should be in the PhysicsComponent.Update() function
	entity.SetPosition(m_currState.GetWorldPosition());
	entity.SetRotation(MathCommon::RadiansToDegrees(m_currState.GetRotInRad()));
}

void CarPhysicsComponent::Brake(float dtTimeMilli)
{
	ApplySlowDownForce(car_brakeForce, dtTimeMilli);
}

void CarPhysicsComponent::DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli)
{
	//halting all movement on the car
	m_newState.SetMomentum(sf::Vector2f(0.0f, 0.0f));
	m_newState.SetWorldPos(m_newState.GetWorldPosition() + dir * dtMilli / 1000.0f * car_dbg_slideSpeed);
	m_newState.Update(dtMilli, car_maxMomentum);
}

sf::Vector2f CarPhysicsComponent::HandleCollision(sf::Vector2f otherEntityMomentum)
{
	auto absorbedMomentum = otherEntityMomentum / 2.0f;
	m_newState.ApplyForce(absorbedMomentum);
	return absorbedMomentum;
}
