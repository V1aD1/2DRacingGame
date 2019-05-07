#pragma once
#include "PhysicsStateV2.h"
#include "../Other/MathCommon.h"
#include "../Entities/Entity.h"
#include "../Other/WorldSpaceManager.h"
#include "VariableCollisionComponent.h"

extern WorldSpaceManager worldSpaceManager;

PhysicsStateV2::PhysicsStateV2(sf::Vector2f pos, float rotRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied) {
	m_worldPos = pos;
	m_rotInRad = rotRad;

	if (cornersWithoutRotationApplied.size() > 0) {
		m_collisionComp = new VariableCollisionComponent(m_worldPos, m_rotInRad, cornersWithoutRotationApplied);
	}

	else { m_collisionComp == nullptr; }
}

PhysicsStateV2::~PhysicsStateV2() {}

void PhysicsStateV2::Update(float dtMilli, float maxVelocity) {
	//update forward dir
	m_forwardDir = sf::Vector2f(std::cos(m_rotInRad), std::sin(m_rotInRad));

	m_velocity += m_acceleration * m_forwardDir;

	//update world position
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

void PhysicsStateV2::UpdateToNewState(const PhysicsStateV2& other)
{
	m_worldPos = other.m_worldPos;
	m_rotInRad = other.m_rotInRad;
	m_forwardDir = other.m_forwardDir;
	m_collisionSpaceCoords = other.m_collisionSpaceCoords;
	m_velocity = other.m_velocity;
	m_acceleration = other.m_acceleration;

	*m_collisionComp = *other.m_collisionComp;
}

PhysicsStateV2::PhysicsStateV2(const PhysicsStateV2& other)
{
	UpdateToNewState(other);
}

PhysicsStateV2& PhysicsStateV2::operator=(const PhysicsStateV2& other)
{
	UpdateToNewState(other);
	return *this;
}

void PhysicsStateV2::Rotate(float radsToTurn) {
	m_rotInRad += radsToTurn;

	//m_forwardDir should be updated in Update() function exclusively,
	//but the driving feels too floaty then, so I'll also update it
	//while turning the car
	m_forwardDir = sf::Vector2f(std::cos(m_rotInRad), std::sin(m_rotInRad));
}

void PhysicsStateV2::SetRotation(float newRotInRad)
{
	m_rotInRad = newRotInRad;

	//todo this is necessary since I don't use acceleration and speed correctly yet
	m_forwardDir = sf::Vector2f(std::cos(m_rotInRad), std::sin(m_rotInRad));
}

void PhysicsStateV2::Accelerate(float acceleration)
{
	m_acceleration += acceleration;
}

void PhysicsStateV2::ApplyForce(sf::Vector2f velocity)
{
	m_velocity += velocity;
}

const std::vector<sf::Vector2f>& PhysicsStateV2::GetWorldCorners() const
{
	if (m_collisionComp) { return m_collisionComp->GetWorldCorners(); }
	else { return std::vector<sf::Vector2f>(); }
}

const std::vector<sf::Vector2i>& PhysicsStateV2::GetCollisionSpaceCoordinates() const
{
	return m_collisionSpaceCoords;
}

sf::Vector2f PhysicsStateV2::GetWorldPosition()
{
	return m_worldPos;
}

sf::Vector2f PhysicsStateV2::GetVelocity()
{
	return m_velocity;
}

sf::Vector2f PhysicsStateV2::GetForwardDir()
{
	return m_forwardDir;
}

float PhysicsStateV2::GetRotInRad()
{
	return m_rotInRad;
}

void PhysicsStateV2::SetWorldPos(sf::Vector2f newPos)
{
	m_worldPos = newPos;
}

void PhysicsStateV2::SetVelocity(sf::Vector2f newVelocity)
{
	m_velocity = newVelocity;
}
