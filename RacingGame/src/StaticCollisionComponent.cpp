#include "include/StaticCollisionComponent.h"

StaticCollisionComponent::StaticCollisionComponent(sf::Vector2f newPos, float newRotInRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied) :
	CollisionComponent(newPos, newRotInRad, cornersWithoutRotationApplied){}


StaticCollisionComponent::~StaticCollisionComponent(){}

void StaticCollisionComponent::Update(sf::Vector2f newPos, float newRotInRad) {
	return;
}

/*const std::vector<sf::Vector2f>& StaticCollisionComponent::GetWorldCorners() const {

}*/