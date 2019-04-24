#include "include/PhysicsState.h"
#include "include/MathCommon.h"
#include "include/Entity.h"
#include "include/WorldSpaceManager.h"
#include "include/VariableCollisionComponent.h"

extern WorldSpaceManager worldSpaceManager;

PhysicsState::PhysicsState(sf::Vector2f pos, float rotRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied) {
	m_worldPos = pos;
	m_rotInRad = rotRad;
	m_collisionComp = new VariableCollisionComponent(m_worldPos, m_rotInRad, cornersWithoutRotationApplied);
}

PhysicsState::~PhysicsState() {}

void PhysicsState::Update(float dtMilli, float maxMomentum) {
	//update forward dir
	m_forwardDir = sf::Vector2f(std::cos(m_rotInRad), std::sin(m_rotInRad));

	//update world position
	if (MathCommon::GetMagnitude(m_momentum) > maxMomentum)
		m_momentum = MathCommon::ChangeLength(m_momentum, maxMomentum);

	m_worldPos = m_worldPos + m_momentum * dtMilli;

	m_collisionComp->Update(m_worldPos, m_rotInRad);

	//save collision space coords
	//this step should happen after worldCorners have been updated!
	auto worldCorners = m_collisionComp->GetWorldCorners();
	m_collisionSpaceCoords = worldSpaceManager.GetCollisionSpaceCoords(std::vector<sf::Vector2f>(std::begin(worldCorners), std::end(worldCorners)));
}

void PhysicsState::UpdateToNewState(const PhysicsState& other)
{
	m_worldPos = other.m_worldPos;
	m_rotInRad = other.m_rotInRad;
	m_forwardDir = other.m_forwardDir;
	m_momentum = other.m_momentum;
	m_collisionSpaceCoords = other.m_collisionSpaceCoords;

	*m_collisionComp = *other.m_collisionComp;
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
	m_rotInRad += radsToTurn;

	//m_forwardDir should be updated in Update() function exclusively,
	//but the driving feels too floaty then, so I'll also update it
	//while turning the car
	m_forwardDir = sf::Vector2f(std::cos(m_rotInRad), std::sin(m_rotInRad));
}

void PhysicsState::Accelerate(float acceleration)
{
	m_momentum += m_forwardDir * acceleration;
}

void PhysicsState::ApplyForce(sf::Vector2f force)
{
	m_momentum += force;
}

const std::vector<sf::Vector2f>& PhysicsState::GetWorldCorners() const
{
	return m_collisionComp->GetWorldCorners();
}

const std::vector<sf::Vector2i>& PhysicsState::GetCollisionSpaceCoordinates() const
{
	return m_collisionSpaceCoords;
}

sf::Vector2f PhysicsState::GetWorldPosition()
{
	return m_worldPos;
}

sf::Vector2f PhysicsState::GetMomentum()
{
	return m_momentum;
}

float PhysicsState::GetRotInRad()
{
	return m_rotInRad;
}

void PhysicsState::SetWorldPos(sf::Vector2f newPos)
{
	m_worldPos = newPos;
}

void PhysicsState::SetMomentum(sf::Vector2f newMomentum)
{
	m_momentum = newMomentum;
}
