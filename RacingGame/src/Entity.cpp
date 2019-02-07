#include "include/Entity.h"



Entity::Entity(sf::Vector2f position, float rot)
{
	m_position = position;
	m_rotation = rot;
}

Entity::~Entity()
{
	//anything to add here?
}

sf::Vector2f Entity::GetPosition() const
{
	return m_position;
}

float Entity::GetRotation() const
{
	return m_rotation;
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

sf::Shape * const Entity::GetShape() const
{
	return m_shape;
}
