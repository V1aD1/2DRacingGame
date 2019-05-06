#include <tuple>

#include "PhysicsComponent.h"
#include "../Entities/Entity.h"
#include "../Other/MathCommon.h"
#include "../Other/WorldSpaceManager.h"

extern WorldSpaceManager worldSpaceManager;

PhysicsComponent::PhysicsComponent(sf::Vector2f pos, 
									float rotRad,
									const std::vector<sf::Vector2f>& cornersWithoutRotationApplied, 
									float maxMomentum, 
									float rotSpeed, 
									float acceleration, 
									float brakeForce, 
									float frictionForce, 
									float dbg_slideSpeed) :
									m_prevState(pos, rotRad, cornersWithoutRotationApplied),
									m_currState(pos, rotRad, cornersWithoutRotationApplied), 
									m_newState(pos, rotRad, cornersWithoutRotationApplied)
{
	m_maxMomentum = maxMomentum;
	m_rotationSpeed = rotSpeed;
	m_acceleration = acceleration;
	m_brakeForce = brakeForce;
	m_frictionForce = frictionForce;
	m_dbg_slideSpeed = dbg_slideSpeed;
}

PhysicsComponent::~PhysicsComponent(){}

///NOTE: function should only be called after computing 
///final position of m_newState
//todo should make static objects also do point in line test!
std::tuple<Entity*, sf::Vector2f> PhysicsComponent::CollisionDetected(Entity& entity) {

	//check every object in same cell(s) as newState
	//for a collision, using point triangle test method
	auto potentialCollisionEntities =  worldSpaceManager.GetEntitiesAtCoords(m_newState.GetCollisionSpaceCoordinates());

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

void PhysicsComponent::Accelerate(float dtTimeMilli, bool forward){
	if (forward)
		m_newState.Accelerate(m_acceleration * (dtTimeMilli / 1000.0f));
	else
		m_newState.Accelerate(-m_acceleration * (dtTimeMilli / 1000.0f));
}

void PhysicsComponent::ApplyFriction(float dtTimeMilli){
	ApplySlowDownForce(m_frictionForce, dtTimeMilli);
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
	float rotAmount = direction * m_rotationSpeed * (dtTimeMilli / 1000.0f);
	m_newState.Rotate(MathCommon::DegreesToRadians(rotAmount));
}

void PhysicsComponent::SetSpeed(float newSpeed)
{
	m_newState.SetMomentum(m_newState.GetForwardDir() * newSpeed);
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
