#include <iostream>

#include "include/Entity.h"
#include "include/MathCommon.h"
#include "include/InputComponent.h"
#include "include/PhysicsComponent.h"
#include "include/GraphicsComponent.h"

Entity::Entity(sf::Vector2f position, float rot, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
{
	m_position = position;
	SetRotation(rot);
	m_input = input;
	m_physics = physics;
	m_graphics = graphics;
}

Entity::~Entity()
{
	delete m_input;
	delete m_physics;
	delete m_graphics;
}

void Entity::Update(sf::RenderWindow& window, float dtTimeMilli, const EventHandler& handler)
{
	//m_input->Update()
	//m_physics->Update()
	//m_graphics->Update()
}

sf::Vector2f Entity::GetPosition() const
{
	return m_position;
}

float Entity::GetRotationInDegrees() const
{
	return m_rotation;
}

float Entity::GetRotationInRadians() const
{
	return m_rotationInRad;
}

sf::Shape * const Entity::GetShape() const
{
	return m_shape;
}

//todo returns COPY of array, maybe should return reference or *?
std::array<sf::Vector2f, 4> Entity::GetWorldCorners() const
{
	auto worldCorners = std::array<sf::Vector2f, 4>();

	for (int i = 0; i < m_localCorners.size(); i++) {
		(worldCorners)[i] = m_localCorners[i] + m_position;
	}

	return worldCorners;
}

void Entity::SetPosition(sf::Vector2f newPos)
{
	m_position = newPos;
}

void Entity::SetRotation(float newRotInDegrees)
{
	m_rotation = newRotInDegrees;
	
	//to avoid potential overflow
	if (m_rotation > 360.0f)
		m_rotation -= 360.0f;
	
	m_rotationInRad = MathCommon::DegreesToRadians(m_rotation);


	if (m_shape) {
		m_shape->setRotation(m_rotation);
	}
}

void Entity::SetCorners(const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied)
{
	m_localCorners = cornersWithoutRotationApplied;

	//orienting corners according to Entity rotation
	for (int i = 0; i < m_localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(m_rotationInRad) - m_localCorners[i].y * std::sin(m_rotationInRad);
		newPoint.y = m_localCorners[i].x * std::sin(m_rotationInRad) + m_localCorners[i].y * std::cos(m_rotationInRad);

		//rotating the point about the centre of the shape
		m_localCorners[i] = newPoint;
	}
}

void Entity::SetShape(sf::Shape * newShape)
{
	m_shape = newShape;
}

//todo find better way to turn,
//I think corners should be turned always according to entity rotation,
//but now they are decoupled
void Entity::Rotate(float degrees)
{
	SetRotation(m_rotation + degrees);

	float radsToTurn = MathCommon::DegreesToRadians(degrees);

	for (int i = 0; i < m_localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(radsToTurn) - m_localCorners[i].y * std::sin(radsToTurn);
		newPoint.y = m_localCorners[i].x * std::sin(radsToTurn) + m_localCorners[i].y * std::cos(radsToTurn);

		//rotating the point about the centre of the shape
		m_localCorners[i] = newPoint;
	}
}