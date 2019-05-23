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

//NOTE: function should only be called after computing 
//final position of m_newState
//todo should make static objects also do point in line test!
//this way we're guaranteed to detect collisions, and can also pinpoint
//location of coollision for spark effect! Need to abstract point in
//triangle collision check to the MathCommon class tho

//todo should rename to DetectCollisionPointInTriangle()
std::tuple<Entity*, sf::Vector2f> PhysicsComponent::DetectCollision(Entity& entity) {

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
			std::vector<sf::Vector2f> otherEntityWorldCorners = *otherEntityCornersPtr;

			for (auto corner : m_newState.GetWorldCorners()) {

				bool collision = true;

				for (size_t i = 0; i < otherEntityWorldCorners.size(); i++) {

					//this operation must be performed in this order!!
					float check = MathCommon::CrossProduct(otherEntityWorldCorners[i] - otherEntityWorldCorners[(i + 1) % otherEntityWorldCorners.size()], otherEntityWorldCorners[i] - (corner));

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

//todo nice and eloquent, but unfortunately doesn't determine point of collision,
//so can't do the spark effect. Instead, continue to use point in triangle method,
//but if no collision is detected, run it from the other entity's point of view,
//and broadcast the results back
std::tuple<Entity*, sf::Vector2f> PhysicsComponent::DetectCollisionLineTest(Entity& entity)
{

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
			if (MathCommon::AreColliding(*otherEntityCornersPtr, m_newState.GetWorldCorners()))
				return std::make_tuple(otherEntity, sf::Vector2f());			
		}
	}

	return std::make_tuple(nullptr, sf::Vector2f());
}

void PhysicsComponent::Accelerate(float dtTimeMilli, bool forward) {
	if (forward)
		m_newState.SetCurrentAcceleration(m_acceleration);
	else
		m_newState.SetCurrentAcceleration(-m_acceleration);
}

//turns off acceleration for this object, if it is accelerating
void PhysicsComponent::Decelerate(float dtTimeMilli)
{
	m_newState.SetCurrentAcceleration(0);
}

void PhysicsComponent::ApplyFriction(float dtTimeMilli) {
	SlowDown(m_frictionDeceleration, dtTimeMilli);
}

void PhysicsComponent::Brake(Entity& entity, float dtTimeMilli)
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
		m_newState.SetCurrentAcceleration(0);
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

//this function sets the acceleration of this object,
//use the Accelerate() function to actually APPLY the acceleration
void PhysicsComponent::SetAcceleration(float newAcc)
{
	m_acceleration = newAcc;
}

void PhysicsComponent::Update(Entity& entity, float dtMilli)
{
	entity.SetPosition(m_currState.GetWorldPosition());
	entity.SetRotation(MathCommon::RadiansToDegrees(m_currState.GetRotInRad()));
}

void PhysicsComponent::DBG_Slide(Entity& entity, const sf::Vector2f & dir, float dtMilli)
{
}

sf::Vector2f PhysicsComponent::HandleCollision(sf::Vector2f otherEntityVelocity)
{
	return sf::Vector2f();
}
