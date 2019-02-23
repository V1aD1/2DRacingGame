#include "include/PhysicsComponent.h"
#include "include/Entity.h"
#include "include/MathCommon.h"

extern std::vector<Entity*> G_STATICOBJECTS;

const float PhysicsComponent::c_length = 40.0f;
const float PhysicsComponent::c_height = 10.0f;

const float PhysicsComponent::c_rotationSpeed = 180.0f;
const float PhysicsComponent::c_acceleration = 0.25f;
const float PhysicsComponent::c_brakeForce = 0.1f;
const float PhysicsComponent::c_frictionForce = 0.1f;
const float PhysicsComponent::c_dbg_slideSpeed = 150.0f;
const float PhysicsComponent::c_maxMomentum = 0.3f;

PhysicsComponent::PhysicsComponent(Entity* entity, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied)
{
	m_currState = CarState(entity, cornersWithoutRotationApplied);
	m_newState = CarState(entity, cornersWithoutRotationApplied);
	m_entity = entity;
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update(float dtMilli)
{
	ApplyFriction(dtMilli);

	if (MathCommon::GetMagnitude(m_newState.momentum) > c_maxMomentum)
		m_newState.momentum = MathCommon::ChangeLength(m_newState.momentum, c_maxMomentum);

	//this calculation MUST ONLY happen in Update() to ensure
	//position isn't getting updated multiple times
	m_newState.worldPos = m_newState.worldPos + m_newState.momentum * dtMilli;

	//update to new state only if NO collision occured
	if (!CollisionDetected())
		m_currState.UpdateToNewState(m_newState);


	else {
		//if collision occurs then halt all momentum on the car
		m_currState.momentum = sf::Vector2f(0.0f, 0.0f);
		m_newState.UpdateToNewState(m_currState);
	}

	//todo this should NOT be happening here!
	m_entity->SetPosition(m_currState.worldPos);
	m_entity->SetRotation(MathCommon::DegreesToRadians(m_currState.rotInRad));
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

			for (auto &carCorner : GetFutureWorldCorners()) {

				bool collision = true;

				for (size_t i = 0; i < objCorners.size(); i++) {

					//this operation must be performed in this order!!
					float check = MathCommon::CrossProduct(objCorners[i] - objCorners[(i + 1) % objCorners.size()], objCorners[i] - (carCorner));

					if (check < 0.0f) {
						collision = false;
						break;
					}
					//todo handle check == 0
				}

				if (collision)
					return true;
			}
		}
	}

	return false;
}

void PhysicsComponent::Accelerate(float dtTimeMilli, bool forward)
{
	if (forward)
		m_newState.momentum += m_newState.forwardDir * c_acceleration * (dtTimeMilli / 1000.0f);
	else
		m_newState.momentum += -(m_newState.forwardDir * c_acceleration * (dtTimeMilli / 1000.0f));
}

void PhysicsComponent::Brake(float dtTimeMilli)
{
	ApplySlowDownForce(c_brakeForce, dtTimeMilli);
}

void PhysicsComponent::DBG_Slide(const sf::Vector2f& dir, float dtMilli)
{
	//halting all movement on the car
	m_newState.momentum = sf::Vector2f(0.0f, 0.0f);
	m_currState.momentum = sf::Vector2f(0.0f, 0.0f);

	//placing car to exact position
	m_entity->SetPosition(m_entity->GetPosition() + dir * dtMilli / 1000.0f * c_dbg_slideSpeed);
	m_entity->SetPosition(m_entity->GetPosition());
}

void PhysicsComponent::ApplyFriction(float dtTimeMilli)
{
	ApplySlowDownForce(c_frictionForce, dtTimeMilli);
}

void PhysicsComponent::ApplySlowDownForce(float forceMag, float dtTimeMilli)
{
	sf::Vector2f momentumDir = MathCommon::Normalize(m_newState.momentum);
	sf::Vector2f stoppingForceToApply = MathCommon::Normalize(m_newState.momentum) * forceMag * (dtTimeMilli / 1000.0f);

	float momentumMag = MathCommon::GetMagnitude(m_newState.momentum);
	float stoppingForceMag = MathCommon::GetMagnitude(stoppingForceToApply);

	//to ensure stopping force doesn't cause car to move backwards
	if (momentumMag > stoppingForceMag)
		m_newState.momentum -= stoppingForceToApply;
	else
		m_newState.momentum = sf::Vector2f(0.0f, 0.0f);
}

void PhysicsComponent::Rotate(float dtTimeMilli, bool left)
{
	int direction = left ? -1 : 1;

	float rotAmount = direction * c_rotationSpeed * (dtTimeMilli / 1000.0f);

	//todo not sure this should be happening here, but it's either here or in the input component
	m_entity->Rotate(rotAmount);

	m_newState.forwardDir = sf::Vector2f(std::cos(m_entity->GetRotationInRadians()), std::sin(m_entity->GetRotationInRadians()));
	m_newState.Rotate(MathCommon::DegreesToRadians(rotAmount), m_entity->GetPosition());
}

//todo returns COPY of array, maybe should return reference or *?
const std::array<sf::Vector2f, 4>& PhysicsComponent::GetWorldCorners() const
{
	return m_currState.m_worldCorners;
}

//todo returns COPY of array, maybe should return reference or *?
std::array<sf::Vector2f, 4> PhysicsComponent::GetFutureWorldCorners() const
{
	auto worldCorners = std::array<sf::Vector2f, 4>();

	for (int i = 0; i < m_newState.m_localCorners.size(); i++) {
		(worldCorners)[i] = m_newState.m_localCorners[i] + m_newState.worldPos;
	}

	return worldCorners;
}
