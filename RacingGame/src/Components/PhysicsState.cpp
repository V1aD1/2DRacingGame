#pragma once
#include "PhysicsState.h"
#include "../Other/MathCommon.h"
#include "../Entities/Entity.h"
#include "../Other/WorldSpaceManager.h"
#include "VariableCollisionComponent.h"

extern WorldSpaceManager worldSpaceManager;

PhysicsState::PhysicsState(sf::Vector2f pos, float rotRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied) {
	m_worldPos = pos;
	SetRotation(rotRad);

	if (cornersWithoutRotationApplied.size() > 0) {
		m_collisionComp = new VariableCollisionComponent(m_worldPos, m_rotInRad, cornersWithoutRotationApplied);
	}

	else { m_collisionComp = nullptr; }
}

PhysicsState::~PhysicsState() {}

//todo currently the only way to change velocity is thorugh acceleration
//but if the entity is turning, shouldn't it's velocity also kinda turn?
//right now it's more like rockets in space instead of cars
//some thoughts, make the car drift if the brake is being applied
//that means that friction on the wheels is smaller, so that's why the car slides
//in which case, the braking is actually dependant on the velocity and direction
//of the car. Braking is more effective the smaller the angle is between
//those two vectors
void PhysicsState::Update(float dtMilli, float maxVelocity) {
	
	//update world position
	m_velocity += m_currentAcceleration * m_forwardDir * (dtMilli / 1000.0f);

	if (MathCommon::GetMagnitude(m_velocity) > maxVelocity)
		m_velocity = MathCommon::ChangeLength(m_velocity, maxVelocity);

	m_worldPos = m_worldPos + m_velocity * dtMilli;

	if (m_collisionComp) { m_collisionComp->Update(m_worldPos, m_rotInRad); }

	//save collision space coords
	//this step should happen after worldCorners have been updated!
	if (m_collisionComp) {
		auto worldCorners = m_collisionComp->GetWorldCorners();
		m_collisionSpaceCoords = worldSpaceManager.GetCollisionSpaceCoords(std::vector<sf::Vector2f>(std::begin(worldCorners), std::end(worldCorners)));
	}
}

void PhysicsState::UpdateToNewState(const PhysicsState& other)
{
	m_worldPos = other.m_worldPos;
	m_rotInRad = other.m_rotInRad;
	m_forwardDir = other.m_forwardDir;
	m_collisionSpaceCoords = other.m_collisionSpaceCoords;
	m_velocity = other.m_velocity;
	m_currentAcceleration = other.m_currentAcceleration;

	*m_collisionComp = *other.m_collisionComp;
}

void PhysicsState::UpdateForwardDir() {
	m_forwardDir = sf::Vector2f(std::cos(m_rotInRad), std::sin(m_rotInRad));
}

PhysicsState::PhysicsState(const PhysicsState& other)
{
	UpdateToNewState(other);
}

PhysicsState& PhysicsState::operator=(const PhysicsState& other)
{
	UpdateToNewState(other);
	return *this;
}

void PhysicsState::Rotate(float radsToTurn) {
	SetRotation(m_rotInRad + radsToTurn);
}

void PhysicsState::SetRotation(float newRotInRad)
{
	m_rotInRad = newRotInRad;
	UpdateForwardDir();
}

void PhysicsState::SetCurrentAcceleration(float newAcc)
{
	m_currentAcceleration = newAcc;
}

void PhysicsState::ApplyVelocity(sf::Vector2f velocity)
{
	m_velocity += velocity;
}

const std::vector<sf::Vector2f>& PhysicsState::GetWorldCorners() const
{
	if (m_collisionComp) { return m_collisionComp->GetWorldCorners(); }
	else { return std::vector<sf::Vector2f>(); }
}

const std::vector<sf::Vector2i>& PhysicsState::GetCollisionSpaceCoordinates() const
{
	return m_collisionSpaceCoords;
}

sf::Vector2f PhysicsState::GetWorldPosition() const
{
	return m_worldPos;
}

sf::Vector2f PhysicsState::GetVelocity() const
{
	return m_velocity;
}

sf::Vector2f PhysicsState::GetForwardDir() const
{
	return m_forwardDir;
}

float PhysicsState::GetRotInRad() const
{
	return m_rotInRad;
}

float PhysicsState::GetCurrentAcceleration() const
{
	return m_currentAcceleration;
}

void PhysicsState::SetWorldPos(sf::Vector2f newPos)
{
	m_worldPos = newPos;
}

void PhysicsState::SetVelocity(sf::Vector2f newVelocity)
{
	m_velocity = newVelocity;
}

std::tuple<bool, sf::Vector2f> PhysicsState::IsColliding(const std::vector<sf::Vector2f>* otherEntityWorldCornersPtr) const
{
	return m_collisionComp->IsColliding(otherEntityWorldCornersPtr);
}
