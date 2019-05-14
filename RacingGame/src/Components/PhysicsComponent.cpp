#include <tuple>

#include "PhysicsComponent.h"
#include "../Entities/Entity.h"
#include "../Other/MathCommon.h"
#include "../Other/WorldSpaceManager.h"

extern WorldSpaceManager worldSpaceManager;

PhysicsComponent::PhysicsComponent(sf::Vector2f pos,
	float rotRad,
	const std::vector<sf::Vector2f>& cornersWithoutRotationApplied,
	float maxSpeed,
	float rotSpeed,
	float acceleration,
	float frictionDeceleration) :
	m_prevState(pos, rotRad, cornersWithoutRotationApplied),
	m_currState(pos, rotRad, cornersWithoutRotationApplied),
	m_newState(pos, rotRad, cornersWithoutRotationApplied)
{
	m_maxSpeed = maxSpeed;
	m_rotationSpeed = rotSpeed;
	m_acceleration = acceleration;
	m_frictionDeceleration = frictionDeceleration;
}

PhysicsComponent::~PhysicsComponent() {}

///NOTE: function should only be called after computing 
///final position of m_newState
//todo should make static objects also do point in line test!
std::tuple<Entity*, sf::Vector2f> PhysicsComponent::CollisionDetected(Entity& entity) {

	//check every object in same cell(s) as newState
	//for a collision, using point triangle test method
	auto potentialCollisionEntities = worldSpaceManager.GetEntitiesAtCoords(m_newState.GetCollisionSpaceCoordinates());

	//check every static object for a collision
	//using point triangle test method
	for (auto otherEntity : potentialCollisionEntities) {

		//to avoid collision detection with itself
		//todo change to use ID of objects instead
		if (otherEntity == &entity)
			continue;

		auto otherEntityCornersPtr = otherEntity->GetWorldCorners();

		if (otherEntityCornersPtr) {
			std::vector<sf::Vector2f> objCorners = *otherEntityCornersPtr;

			for (auto corner : m_newState.GetWorldCorners()) {

				bool collision = true;

				for (size_t i = 0; i < objCorners.size(); i++) {

					//this operation must be performed in this order!!
					float check = MathCommon::CrossProduct(objCorners[i] - objCorners[(i + 1) % objCorners.size()], objCorners[i] - (corner));

					if (check <= 0.0f) {
						collision = false;
						break;
					}
				}
				if (collision) {
					return std::make_tuple(otherEntity, corner);
				}
			}
		}
	}

	return std::make_tuple(nullptr, sf::Vector2f());
}

//todo should be pure and implemented in carphysicscomponent?
void PhysicsComponent::Accelerate(float dtTimeMilli, bool forward) {
	if (forward)
		m_newState.SetAcceleration(m_acceleration);
	else
		m_newState.SetAcceleration(-m_acceleration);
}

void PhysicsComponent::ApplyFriction(float dtTimeMilli) {
	SlowDown(m_frictionDeceleration, dtTimeMilli);
}

void PhysicsComponent::Brake(float dtTimeMilli)
{
}

const std::vector<sf::Vector2i>& PhysicsComponent::GetCollisionSpaceCoords()
{
	return m_currState.GetCollisionSpaceCoordinates();
}

const std::vector<sf::Vector2i>& PhysicsComponent::GetPrevCollisionSpaceCoords()
{
	return m_prevState.GetCollisionSpaceCoordinates();
}

sf::Vector2f PhysicsComponent::GetForwardDir()
{
	return m_currState.GetForwardDir();
}

void PhysicsComponent::SlowDown(float deceleration, float dtTimeMilli) {

	auto newStateVelocity = m_newState.GetVelocity();

	if (MathCommon::GetMagnitude(newStateVelocity) == 0)
		return;

	sf::Vector2f velocityDir = MathCommon::Normalize(newStateVelocity);
	sf::Vector2f stoppingVelocityToApply = MathCommon::Normalize(newStateVelocity) * deceleration * (dtTimeMilli / 1000.0f) * -1.0f;

	float vMag = MathCommon::GetMagnitude(newStateVelocity);
	float stoppingVelocityMag = MathCommon::GetMagnitude(stoppingVelocityToApply);

	//to ensure stopping force doesn't cause car to move backwards
	if (vMag > stoppingVelocityMag) {
		m_newState.ApplyVelocity(stoppingVelocityToApply);
	}
	else {
		m_newState.SetVelocity(sf::Vector2f(0.0f, 0.0f));
		m_newState.SetAcceleration(0);
	}
}

void PhysicsComponent::Rotate(float dtTimeMilli, bool left) {
	int direction = left ? -1 : 1;
	float rotAmount = direction * m_rotationSpeed * (dtTimeMilli / 1000.0f);
	m_newState.Rotate(MathCommon::DegreesToRadians(rotAmount));
}

void PhysicsComponent::SetSpeed(float newSpeed)
{
	m_newState.SetVelocity(m_newState.GetForwardDir() * newSpeed);
}

void PhysicsComponent::SetMaxSpeed(float newMaxSpeed)
{
	m_maxSpeed = newMaxSpeed;
}

void PhysicsComponent::SetPosition(sf::Vector2f newPos)
{
	m_currState.SetWorldPos(newPos);
	m_newState.SetWorldPos(newPos);
}

void PhysicsComponent::SetRotation(float newRotInRad)
{
	m_currState.SetRotation(newRotInRad);
	m_newState.SetRotation(newRotInRad);
}

//todo the relationship between m_acceleration and the 
//acceleration of the various physicsStates is unclear
void PhysicsComponent::SetAcceleration(float newAcc)
{
	m_acceleration = newAcc;
	m_currState.SetAcceleration(newAcc);
	m_newState.SetAcceleration(newAcc);
}
