#include <tuple>

#include "PhysicsComponentV2.h"
#include "../Entities/Entity.h"
#include "../Other/MathCommon.h"
#include "../Other/WorldSpaceManager.h"

extern WorldSpaceManager worldSpaceManager;

PhysicsComponentV2::PhysicsComponentV2(sf::Vector2f pos,
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

PhysicsComponentV2::~PhysicsComponentV2() {}

///NOTE: function should only be called after computing 
///final position of m_newState
//todo should make static objects also do point in line test!
std::tuple<Entity*, sf::Vector2f> PhysicsComponentV2::CollisionDetected(Entity& entity) {

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

void PhysicsComponentV2::Accelerate(float dtTimeMilli, bool forward) {
	if (forward)
		m_newState.Accelerate(m_acceleration * (dtTimeMilli / 1000.0f));
	else
		m_newState.Accelerate(-m_acceleration * (dtTimeMilli / 1000.0f));
}

void PhysicsComponentV2::ApplyFriction(float dtTimeMilli) {
	auto deceleration = m_frictionDeceleration * dtTimeMilli / 1000.0f;

	if (m_newState.GetAcceleration() < deceleration )
		m_newState.SetAcceleration(0);
	else
		m_newState.Accelerate(-deceleration);
}

const std::vector<sf::Vector2i>& PhysicsComponentV2::GetCollisionSpaceCoords()
{
	return m_currState.GetCollisionSpaceCoordinates();
}

const std::vector<sf::Vector2i>& PhysicsComponentV2::GetPrevCollisionSpaceCoords()
{
	return m_prevState.GetCollisionSpaceCoordinates();
}

sf::Vector2f PhysicsComponentV2::GetForwardDir()
{
	return m_currState.GetForwardDir();
}

void PhysicsComponentV2::SlowDown(float deceleration, float dtTimeMilli) {

	auto newStateVelocity = m_newState.GetVelocity();

	sf::Vector2f velocityDir = MathCommon::Normalize(newStateVelocity);
	sf::Vector2f stoppingVelocityToApply = MathCommon::Normalize(newStateVelocity) * deceleration * (dtTimeMilli / 1000.0f) * -1.0f;

	float vMag = MathCommon::GetMagnitude(newStateVelocity);
	float stoppingVelocityMag = MathCommon::GetMagnitude(stoppingVelocityToApply);

	//to ensure stopping force doesn't cause car to move backwards
	if (vMag > stoppingVelocityMag)
		m_newState.ApplyForce(stoppingVelocityToApply);
	else
		m_newState.SetVelocity(sf::Vector2f(0.0f, 0.0f));
}

void PhysicsComponentV2::Rotate(float dtTimeMilli, bool left) {
	int direction = left ? -1 : 1;
	float rotAmount = direction * m_rotationSpeed * (dtTimeMilli / 1000.0f);
	m_newState.Rotate(MathCommon::DegreesToRadians(rotAmount));
}

void PhysicsComponentV2::SetSpeed(float newSpeed)
{
	m_newState.SetVelocity(m_newState.GetForwardDir() * newSpeed);
}

void PhysicsComponentV2::SetPosition(sf::Vector2f newPos)
{
	m_currState.SetWorldPos(newPos);
	m_newState.SetWorldPos(newPos);
}

void PhysicsComponentV2::SetRotation(float newRotInRad)
{
	m_currState.SetRotation(newRotInRad);
	m_newState.SetRotation(newRotInRad);
}
