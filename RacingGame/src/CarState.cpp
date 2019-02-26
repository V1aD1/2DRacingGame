#include "include/CarState.h"
#include "include/MathCommon.h"
#include "include/Entity.h"

const float CarState::c_maxMomentum = 0.3f;

CarState::CarState(Entity* entity, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied){
	m_localCorners = cornersWithoutRotationApplied;

	m_rotInRad = entity->GetRotationInRadians();
	m_worldPos = entity->GetPosition();
}

CarState::~CarState() {}

void CarState::Update(float dtMilli) {
	//update forward dir
	m_forwardDir = sf::Vector2f(std::cos(m_rotInRad), std::sin(m_rotInRad));

	//update world position
	if (MathCommon::GetMagnitude(m_momentum) > c_maxMomentum)
		m_momentum = MathCommon::ChangeLength(m_momentum, c_maxMomentum);

	m_worldPos = m_worldPos + m_momentum * dtMilli;

	//update m_worldCoords
	for (int i = 0; i < m_localCorners.size(); i++) {
		m_worldCorners[i] = m_localCorners[i] + m_worldPos;
	}

	//orienting corners according to Entity rotation
	for (int i = 0; i < m_localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(m_rotInRad) - m_localCorners[i].y * std::sin(m_rotInRad);
		newPoint.y = m_localCorners[i].x * std::sin(m_rotInRad) + m_localCorners[i].y * std::cos(m_rotInRad);

		//rotating the point about the centre of the shape
		m_worldCorners[i] = newPoint + m_worldPos;
	}
}

CarState::CarState(const CarState & other)
{
	m_worldPos = other.m_worldPos;
	m_rotInRad = other.m_rotInRad;
	m_forwardDir = other.m_forwardDir;
	m_momentum = other.m_momentum;
	m_localCorners = other.m_localCorners;
	m_worldCorners = other.m_worldCorners;
}

CarState & CarState::operator=(const CarState & other)
{
	m_worldPos = other.m_worldPos;
	m_rotInRad = other.m_rotInRad;
	m_forwardDir = other.m_forwardDir;
	m_momentum = other.m_momentum;
	m_localCorners = other.m_localCorners;
	m_worldCorners = other.m_worldCorners;

	return *this;
}

void CarState::Rotate(float radsToTurn){
	m_rotInRad += radsToTurn;
	
	//m_forwardDir should be updated in Update() function exclusively,
	//but the driving feels too floaty then, so I'll also update it
	//while turning the car
	m_forwardDir = sf::Vector2f(std::cos(m_rotInRad), std::sin(m_rotInRad));
}

void CarState::Accelerate(float acceleration)
{
	m_momentum += m_forwardDir * acceleration;
}

void CarState::ApplyForce(sf::Vector2f force)
{
	m_momentum += force;
}

const std::array<sf::Vector2f, 4>* CarState::GetWorldCorners() const
{
	return &m_worldCorners;
}

sf::Vector2f CarState::GetWorldPosition()
{
	return m_worldPos;
}

sf::Vector2f CarState::GetMomentum()
{
	return m_momentum;
}

void CarState::SetWorldPos(sf::Vector2f newPos)
{
	m_worldPos = newPos;
}

void CarState::SetMomentum(sf::Vector2f newMomentum)
{
	m_momentum = newMomentum;
}
