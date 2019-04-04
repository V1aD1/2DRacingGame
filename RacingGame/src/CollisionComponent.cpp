#include <array>
#include <SFML/Graphics.hpp>

#include "include/CollisionComponent.h"
#include "include/Entity.h"

CollisionComponent::CollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied)
{
	m_localCorners = cornersWithoutRotationApplied;
	Update(newPos, newRotInRad);
}


CollisionComponent::~CollisionComponent(){}

CollisionComponent& CollisionComponent::operator=(const CollisionComponent & other)
{
	m_localCorners = other.m_localCorners;
	m_worldCorners = other.m_worldCorners;
	return *this;
}

//Updates m_worldCorners to latest positions
void CollisionComponent::Update(sf::Vector2f newPos, float newRotInRad)
{
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

const std::array<sf::Vector2f, 4>& CollisionComponent::GetWorldCorners() const
{
	return m_worldCorners;
}
