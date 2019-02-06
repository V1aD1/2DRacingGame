#include <array>
#include <SFML/Graphics.hpp>

#pragma once
class Entity
{
public:
	Entity();
	~Entity();

	sf::Vector2f GetPosition() const;
	float GetRotation() const;
	
	std::unique_ptr<std::array<sf::Vector2f, 4>> const GetWorldCorners() const;
	sf::Shape* const GetShape() const;

private:
	sf::Vector2f position;
	float rotation;

	std::array<sf::Vector2f, 4> localCorners;
	sf::Shape* shape;
};

