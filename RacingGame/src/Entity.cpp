#include "include/Entity.h"
#include "include/MathCommon.h"


Entity::Entity(sf::Vector2f position, float rot)
{
	m_position = position;
	m_rotation = rot;
	m_rotationInRad = MathCommon::DegreesToRadians(GetRotation());
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

void Entity::SetPosition(sf::Vector2f newPos)
{
	m_position = newPos;
}

void Entity::SetCorners(const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied)
{
	m_localCorners = cornersWithoutRotationApplied;

	for (int i = 0; i < 4; i++) {

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

void Entity::Rotate(float degrees)
{
	//todo
}
