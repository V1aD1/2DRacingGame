#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
}

sf::Vector2f Entity::GetPosition() const
{
	return position;
}

float Entity::GetRotation() const
{
	return rotation;
}

std::unique_ptr<std::array<sf::Vector2f, 4>> const Entity::GetWorldCorners() const
{
	std::unique_ptr<std::array<sf::Vector2f, 4>> ptr(new std::array<sf::Vector2f, 4>);
	
	for (int i = 0; i < localCorners.size(); i++) {
		(*ptr)[i] = localCorners[i] + position;
	}

	return ptr;
	
}

sf::Shape * const Entity::GetShape() const
{
	return nullptr;
}
