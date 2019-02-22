#include "include/CarState.h"
#include "include/MathCommon.h"

CarState::CarState(std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied){
	m_localCorners = cornersWithoutRotationApplied;
}

void CarState::UpdateToNewState(const CarState& newState) {
	forwardDir = newState.forwardDir;
	momentum = newState.momentum;
	m_localCorners = newState.m_localCorners;
}

CarState::~CarState() {
}
