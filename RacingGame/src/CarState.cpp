#include "include/CarState.h"
#include "include/MathCommon.h"
#include "include/Entity.h"

CarState::CarState(Entity* entity, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied){
	m_localCorners = cornersWithoutRotationApplied;

	m_rotInRad = entity->GetRotationInRadians();
	m_worldPos = entity->GetPosition();

	//orienting corners according to Entity rotation
	for (int i = 0; i < m_localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(m_rotInRad) - m_localCorners[i].y * std::sin(m_rotInRad);
		newPoint.y = m_localCorners[i].x * std::sin(m_rotInRad) + m_localCorners[i].y * std::cos(m_rotInRad);

		//rotating the point about the centre of the shape
		m_localCorners[i] = newPoint;
	}

	for (int i = 0; i < m_localCorners.size(); i++) {
		m_worldCorners[i] = m_localCorners[i] + m_worldPos;
	}
}

CarState::~CarState() {}

void CarState::UpdateToNewState(const CarState& newState) {
	m_worldPos = newState.m_worldPos;
	m_rotInRad = newState.m_rotInRad;
	m_forwardDir = newState.m_forwardDir;
	m_momentum = newState.m_momentum;
	m_localCorners = newState.m_localCorners;
	m_worldCorners = newState.m_worldCorners;
}

//todo find better way to turn,
//I think corners should be turned always according to entity rotation,
//but now they are decoupled
void CarState::Rotate(float radsToTurn){
	m_rotInRad += radsToTurn;
	for (int i = 0; i < m_localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(radsToTurn) - m_localCorners[i].y * std::sin(radsToTurn);
		newPoint.y = m_localCorners[i].x * std::sin(radsToTurn) + m_localCorners[i].y * std::cos(radsToTurn);

		//rotating the point about the centre of the shape
		m_localCorners[i] = newPoint;
	}

	for (int i = 0; i < m_localCorners.size(); i++) {
		m_worldCorners[i] = m_localCorners[i] + m_worldPos;
	}

	m_forwardDir = sf::Vector2f(std::cos(m_rotInRad), std::sin(m_rotInRad));
}