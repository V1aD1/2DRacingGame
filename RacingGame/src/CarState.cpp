#include "include/CarState.h"
#include "include/MathCommon.h"
#include "include/Entity.h"

CarState::CarState() {
	//nothing should enter here
	;
}

CarState::CarState(Entity* entity, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied){
	m_localCorners = cornersWithoutRotationApplied;
	rotInRad = entity->GetRotationInRadians();
	worldPos = entity->GetPosition();

	//orienting corners according to Entity rotation
	for (int i = 0; i < m_localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(rotInRad) - m_localCorners[i].y * std::sin(rotInRad);
		newPoint.y = m_localCorners[i].x * std::sin(rotInRad) + m_localCorners[i].y * std::cos(rotInRad);

		//rotating the point about the centre of the shape
		m_localCorners[i] = newPoint;
	}
}

CarState::~CarState() {}

void CarState::UpdateToNewState(const CarState& newState) {
	worldPos = newState.worldPos;
	rotInRad = newState.rotInRad;
	forwardDir = newState.forwardDir;
	momentum = newState.momentum;
	m_localCorners = newState.m_localCorners;
}

//todo find better way to turn,
//I think corners should be turned always according to entity rotation,
//but now they are decoupled
void CarState::Rotate(float radsToTurn)
{
	for (int i = 0; i < m_localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(radsToTurn) - m_localCorners[i].y * std::sin(radsToTurn);
		newPoint.y = m_localCorners[i].x * std::sin(radsToTurn) + m_localCorners[i].y * std::cos(radsToTurn);

		//rotating the point about the centre of the shape
		m_localCorners[i] = newPoint;
	}
}