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
					m_currState(entity, cornersWithoutRotationApplied),
					m_newState(entity, cornersWithoutRotationApplied){}

PhysicsComponent::~PhysicsComponent(){}

void PhysicsComponent::Update(Entity& entity, float dtMilli){
	ApplyFriction(dtMilli);

	if (MathCommon::GetMagnitude(m_newState.m_momentum) > c_maxMomentum)
		m_newState.m_momentum = MathCommon::ChangeLength(m_newState.m_momentum, c_maxMomentum);

	//this calculation MUST ONLY happen in Update() to ensure position isn't getting updated multiple times
	m_newState.m_worldPos = m_newState.m_worldPos + m_newState.m_momentum * dtMilli;
	
	//update corners
	for (int i = 0; i < m_newState.m_localCorners.size(); i++) {
		m_newState.m_worldCorners[i] = m_newState.m_localCorners[i] + m_newState.m_worldPos;
	}

	//update to new state only if NO collision occured
	if (!CollisionDetected())
		m_currState.UpdateToNewState(m_newState);

	//if collision occurs then halt all momentum on the car
	else {
		m_currState.m_momentum = sf::Vector2f(0.0f, 0.0f);
		m_newState.UpdateToNewState(m_currState);
	}

	entity.SetPosition(m_currState.m_worldPos);
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

			for (auto &carCorner : m_newState.m_worldCorners) {

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
		m_newState.m_momentum += m_newState.m_forwardDir * c_acceleration * (dtTimeMilli / 1000.0f);
	else
		m_newState.m_momentum += -(m_newState.m_forwardDir * c_acceleration * (dtTimeMilli / 1000.0f));
}

void PhysicsComponent::Brake(float dtTimeMilli){
	ApplySlowDownForce(c_brakeForce, dtTimeMilli);
}

void PhysicsComponent::DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli){
	//halting all movement on the car
	m_newState.m_momentum = sf::Vector2f(0.0f, 0.0f);
	m_newState.m_worldPos += dir * dtMilli / 1000.0f * c_dbg_slideSpeed;
	
	for (int i = 0; i < m_newState.m_localCorners.size(); i++) {
		m_newState.m_worldCorners[i] = m_newState.m_localCorners[i] + m_newState.m_worldPos;
	}

	//ensuring current state matches new state
	m_currState.UpdateToNewState(m_newState);

	//placing car to exact position
	entity.SetPosition(m_newState.m_worldPos);
	entity.SetRotation(MathCommon::RadiansToDegrees(m_newState.m_rotInRad));
}

void PhysicsComponent::ApplyFriction(float dtTimeMilli){
	ApplySlowDownForce(c_frictionForce, dtTimeMilli);
}

void PhysicsComponent::ApplySlowDownForce(float forceMag, float dtTimeMilli){
	sf::Vector2f momentumDir = MathCommon::Normalize(m_newState.m_momentum);
	sf::Vector2f stoppingForceToApply = MathCommon::Normalize(m_newState.m_momentum) * forceMag * (dtTimeMilli / 1000.0f);

	float momentumMag = MathCommon::GetMagnitude(m_newState.m_momentum);
	float stoppingForceMag = MathCommon::GetMagnitude(stoppingForceToApply);

	//to ensure stopping force doesn't cause car to move backwards
	if (momentumMag > stoppingForceMag)
		m_newState.m_momentum -= stoppingForceToApply;
	else
		m_newState.m_momentum = sf::Vector2f(0.0f, 0.0f);
}

void PhysicsComponent::Rotate(float dtTimeMilli, bool left){
	int direction = left ? -1 : 1;

	float rotAmount = direction * c_rotationSpeed * (dtTimeMilli / 1000.0f);

	m_newState.Rotate(MathCommon::DegreesToRadians(rotAmount));
}

const std::array<sf::Vector2f, 4>* PhysicsComponent::GetWorldCorners() const{
	return &(m_currState.m_worldCorners);
}
