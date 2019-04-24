#include <array>
#include <SFML/Graphics.hpp>

#include "include/CollisionComponent.h"

CollisionComponent::CollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied)
{
	m_localCorners = cornersWithoutRotationApplied;
	Update(newPos, newRotInRad);
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
