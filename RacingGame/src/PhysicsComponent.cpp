#include "include/PhysicsComponent.h"
#include "include/Entity.h"
#include "include/MathCommon.h"

extern std::vector<Entity*> G_STATICOBJECTS;

const float PhysicsComponent::c_rotationSpeed = 180.0f;
const float PhysicsComponent::c_acceleration = 0.25f;
const float PhysicsComponent::c_brakeForce = 0.1f;
const float PhysicsComponent::c_frictionForce = 0.1f;
const float PhysicsComponent::c_dbg_slideSpeed = 150.0f;
const float PhysicsComponent::c_maxMomentum = 0.3f;

PhysicsComponent::PhysicsComponent(Entity* entity, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied): 
					m_currState(entity, cornersWithoutRotationApplied, c_maxMomentum),
					m_newState(entity, cornersWithoutRotationApplied, c_maxMomentum){}

PhysicsComponent::~PhysicsComponent(){}

void PhysicsComponent::Update(Entity& entity, float dtMilli){
	ApplyFriction(dtMilli);

	m_newState.Update(dtMilli);

	//update to new state only if NO collision occured
	if (!CollisionDetected())
		m_currState = m_newState;

	//if collision occurs then halt all momentum on the car
	else {
		m_currState.SetMomentum(sf::Vector2f(0.0f, 0.0f));
		m_newState = m_currState;
	}

	entity.SetPosition(m_currState.GetWorldPosition());
	entity.SetRotation(MathCommon::RadiansToDegrees(m_currState.m_rotInRad));
}

///NOTE: function should only be called after computing 
///final position of m_newState
bool PhysicsComponent::CollisionDetected() {
	//check every static object for a collision
	//using point triangle test method
	for (auto object : G_STATICOBJECTS) {

		auto objCornersPtr = object->GetWorldCorners();

		if (objCornersPtr) {

			std::array<sf::Vector2f, 4> objCorners = *objCornersPtr;

			for (auto &carCorner : *(m_newState.GetWorldCorners())) {

				bool collision = true;

				for (size_t i = 0; i < objCorners.size(); i++) {

					//this operation must be performed in this order!!
					float check = MathCommon::CrossProduct(objCorners[i] - objCorners[(i + 1) % objCorners.size()], objCorners[i] - (carCorner));

					if (check <= 0.0f) {
						collision = false;
						break;
					}
				}
				if (collision)
					return true;
			}
		}
	}

	return false;
}

void PhysicsComponent::Accelerate(float dtTimeMilli, bool forward){
	if (forward)
		m_newState.Accelerate(c_acceleration * (dtTimeMilli / 1000.0f));
	else
		m_newState.Accelerate(-c_acceleration * (dtTimeMilli / 1000.0f));
}

void PhysicsComponent::Brake(float dtTimeMilli){
	ApplySlowDownForce(c_brakeForce, dtTimeMilli);
}

void PhysicsComponent::DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli){
	//halting all movement on the car
	m_newState.SetMomentum(sf::Vector2f(0.0f, 0.0f));
	m_newState.SetWorldPos(m_newState.GetWorldPosition() + dir * dtMilli / 1000.0f * c_dbg_slideSpeed);
	m_newState.Update(dtMilli);

	//ensuring current state matches new state
	m_currState = m_newState;
}

void PhysicsComponent::ApplyFriction(float dtTimeMilli){
	ApplySlowDownForce(c_frictionForce, dtTimeMilli);
}

void PhysicsComponent::ApplySlowDownForce(float forceMag, float dtTimeMilli){

	auto newStateMomentum = m_newState.GetMomentum();

	sf::Vector2f momentumDir = MathCommon::Normalize(newStateMomentum);
	sf::Vector2f stoppingForceToApply = MathCommon::Normalize(newStateMomentum) * forceMag * (dtTimeMilli / 1000.0f) * -1.0f;

	float momentumMag = MathCommon::GetMagnitude(newStateMomentum);
	float stoppingForceMag = MathCommon::GetMagnitude(stoppingForceToApply);

	//to ensure stopping force doesn't cause car to move backwards
	if (momentumMag > stoppingForceMag)
		m_newState.ApplyForce(stoppingForceToApply);
	else
		m_newState.SetMomentum(sf::Vector2f(0.0f, 0.0f));
}

void PhysicsComponent::Rotate(float dtTimeMilli, bool left){
	int direction = left ? -1 : 1;
	float rotAmount = direction * c_rotationSpeed * (dtTimeMilli / 1000.0f);
	m_newState.Rotate(MathCommon::DegreesToRadians(rotAmount));
}

const std::array<sf::Vector2f, 4>* PhysicsComponent::GetWorldCorners() const{
	return m_currState.GetWorldCorners();
}
