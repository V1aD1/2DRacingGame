#include "include/CarState.h"
#include "include/MathCommon.h"

CarState::CarState(sf::Vector2f pos, float rot, sf::Vector2f size) : Entity(pos, rot)
{
	sf::RectangleShape* shape = new sf::RectangleShape(size);
	shape->setFillColor(sf::Color::Blue);
	shape->setOutlineThickness(1.0f);
	shape->setOutlineColor(sf::Color(250, 150, 100));
	shape->setOrigin(size.x / 2.0f, size.y / 2.0f);
	shape->setPosition(0.0f, 0.0f);
	SetShape(shape);

	std::array<sf::Vector2f, 4> corners = std::array<sf::Vector2f, 4>();
	corners[0] = sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f);
	corners[1] = sf::Vector2f(size.x / 2.0f, -size.y / 2.0f);
	corners[2] = sf::Vector2f(size.x / 2.0f, size.y / 2.0f);
	corners[3] = sf::Vector2f(-size.x / 2.0f, size.y / 2.0f);
	SetCorners(corners);
}

void CarState::UpdateToNewState(const CarState& newState) {
	forwardDir = newState.forwardDir;
	momentum = newState.momentum;

	//todo extremely convoluted way to do this, should get rid of Rotate method all together
	Rotate(newState.m_rotation - m_rotation);
	SetPosition(newState.m_position);
	SetRotation(newState.m_rotation);
}

void CarState::ApplyFriction(float fricForce, float dtTimeMilli)
{
	ApplySlowDownForce(fricForce, dtTimeMilli);
}

void CarState::ApplySlowDownForce(float forceMag, float dtTimeMilli)
{
	sf::Vector2f momentumDir = MathCommon::Normalize(momentum);
	sf::Vector2f stoppingForceToApply = MathCommon::Normalize(momentum) * forceMag * (dtTimeMilli / 1000.0f);

	float momentumMag = MathCommon::GetMagnitude(momentum);
	float stoppingForceMag = MathCommon::GetMagnitude(stoppingForceToApply);

	//to ensure stopping force doesn't cause car to move backwards
	if (momentumMag > stoppingForceMag)
		momentum -= stoppingForceToApply;
	else
		momentum = sf::Vector2f(0.0f, 0.0f);
}

CarState::~CarState() {
	delete m_shape;
}
