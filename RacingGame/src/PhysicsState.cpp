#include "include/PhysicsState.h"
#include "include/MathCommon.h"
#include "include/Entity.h"
#include "include/CollisionComponent.h"

PhysicsState::PhysicsState(sf::Vector2f pos, float rotRad, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied) {
	m_worldPos = pos;
	m_rotInRad = rotRad;
	m_collissionComp = new CollisionComponent(m_worldPos, m_rotInRad, cornersWithoutRotationApplied);
}

PhysicsState::~PhysicsState() {}

void PhysicsState::Update(float dtMilli, float maxMomentum) {
	//update forward dir
	m_forwardDir = sf::Vector2f(std::cos(m_rotInRad), std::sin(m_rotInRad));

	//update world position
	if (MathCommon::GetMagnitude(m_momentum) > maxMomentum)
		m_momentum = MathCommon::ChangeLength(m_momentum, maxMomentum);

	m_worldPos = m_worldPos + m_momentum * dtMilli;

	m_collissionComp->Update(m_worldPos, m_rotInRad);
}

PhysicsState::PhysicsState(const PhysicsState & other)
{
	m_worldPos = other.m_worldPos;
	m_rotInRad = other.m_rotInRad;
	m_forwardDir = other.m_forwardDir;
	m_momentum = other.m_momentum;

	//is this right?
	delete m_collissionComp;
	m_collissionComp = new CollisionComponent(*other.m_collissionComp);
}

PhysicsState & PhysicsState::operator=(const PhysicsState & other)
{
	m_worldPos = other.m_worldPos;
	m_rotInRad = other.m_rotInRad;
	m_forwardDir = other.m_forwardDir;
	m_momentum = other.m_momentum;
	
	//is this right?
	delete m_collissionComp;
	m_collissionComp = new CollisionComponent(*other.m_collissionComp);

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

const std::array<sf::Vector2f, 4>* PhysicsState::GetWorldCorners() const
{
	return m_collissionComp->GetWorldCorners();
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
