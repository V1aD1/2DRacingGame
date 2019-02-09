#include <iostream>

#include "include/Entity.h"
#include "include/MathCommon.h"

Entity::Entity(){

}

Entity::Entity(sf::Vector2f position, float rot)
{
	m_position = position;
	SetRotation(rot);
}

Entity::~Entity()
{
}

sf::Vector2f Entity::GetPosition() const
{
	return m_position;
}

float Entity::GetRotation() const
{
	return m_rotation;
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
