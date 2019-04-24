#include <array>
#include <SFML/Graphics.hpp>

#include "include/CollisionComponent.h"

CollisionComponent::CollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied)
{
	m_localCorners = cornersWithoutRotationApplied;

	if (m_worldCorners.size() != m_localCorners.size())
		m_worldCorners.resize(m_localCorners.size());

	//update m_worldCoords
	for (int i = 0; i < m_localCorners.size(); i++) {
		m_worldCorners[i] = m_localCorners[i] + newPos;
	}

	//orienting corners according to Entity rotation
	for (int i = 0; i < m_localCorners.size(); i++) {

		auto newPoint = sf::Vector2f();
		newPoint.x = m_localCorners[i].x * std::cos(newRotInRad) - m_localCorners[i].y * std::sin(newRotInRad);
		newPoint.y = m_localCorners[i].x * std::sin(newRotInRad) + m_localCorners[i].y * std::cos(newRotInRad);

		//rotating the point about the centre of the shape
		m_worldCorners[i] = newPoint + newPos;
	}
}


CollisionComponent::~CollisionComponent(){}

CollisionComponent& CollisionComponent::operator=(const CollisionComponent& other)
{
	m_localCorners = other.m_localCorners;
	m_worldCorners = other.m_worldCorners;
	return *this;
}

const std::vector<sf::Vector2f>& CollisionComponent::GetWorldCorners() const
{
	return m_worldCorners;
}
