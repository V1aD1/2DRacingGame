#include <iostream>

#include "Entity.h"
#include "../Other/MathCommon.h"
#include "../Other/WorldSpaceManager.h"

extern WorldSpaceManager spaceManager;

Entity::Entity()
{
}

Entity::Entity(sf::Vector2f position, float rotDeg) : m_position(position)
{
	SetRotation(rotDeg);
}

Entity::Entity(sf::Vector2f position, float rot, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics, CollisionComponent* collision) : 
				m_position(position), m_input(input), m_physics(physics), m_graphics(graphics), m_collision(collision)
{
	SetRotation(rot);
}

Entity::~Entity()
{
	if (m_input)
		delete m_input;
	if (m_physics)
		delete m_physics;
	if (m_graphics)
		delete m_graphics;
	if (m_collision)
		delete m_collision;
}

void Entity::Update(sf::RenderWindow& window, float dtTimeMilli, const EventHandler& handler)
{
	if (m_input)
		m_input->Update(*this, handler, dtTimeMilli);
	if (m_physics)
		m_physics->Update(*this, dtTimeMilli);
	if (m_collision)
		m_collision->Update(m_position, m_rotationInRad);
	if (m_graphics)
		m_graphics->Update(*this, window, dtTimeMilli);
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

void Entity::SetPosition(sf::Vector2f newPos)
{
	m_position = newPos;

	//necessary because there can be entities with position
	//but without a physics component
	//that's composition for you!
	if(m_physics)
		m_physics->SetPosition(newPos);
}

const std::vector<sf::Vector2f>* Entity::GetWorldCorners() const
{
	if (m_collision)
		return &m_collision->GetWorldCorners();

	return nullptr;
}

const std::vector<sf::Vector2i>* Entity::GetPrevCollisionSpaceCoords() const
{
	if (m_physics)
		return &m_physics->GetPrevCollisionSpaceCoords();
	
	return nullptr;
}


void Entity::SetRotation(float newRotInDegrees)
{
	m_rotation = newRotInDegrees;

	if (m_rotation > 360.0f)
		m_rotation -= 360.0f;

	m_rotationInRad = MathCommon::DegreesToRadians(m_rotation);

	if(m_physics)
		m_physics->SetRotation(m_rotationInRad);
}

void Entity::Rotate(float degrees)
{
	SetRotation(m_rotation + degrees);
}

//if no physics component present, then the object is assumed to
//be static, and therefore absorbs all the momentum from the
//colliding entity
sf::Vector2f Entity::HandleCollision(sf::Vector2f otherEntityVel)
{
	sf::Vector2f absorbedVel = otherEntityVel;

	if (m_physics) {
		absorbedVel = m_physics->HandleCollision(otherEntityVel);
	}

	return absorbedVel;
}
