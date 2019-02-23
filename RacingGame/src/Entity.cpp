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
	m_input->Update(*this, handler, dtTimeMilli);
	m_physics->Update(dtTimeMilli);
	m_graphics->Update(*this, window);
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

//todo returns COPY of array, maybe should return reference or *?
std::array<sf::Vector2f, 4> Entity::GetWorldCorners() const
{
	if(m_physics)
		return m_physics->GetWorldCorners();

	//is this right?
	return std::array<sf::Vector2f, 4>();
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
}

//todo find better way to turn,
//I think corners should be turned always according to entity rotation,
//but now they are decoupled
void Entity::Rotate(float degrees)
{
	SetRotation(m_rotation + degrees);
}