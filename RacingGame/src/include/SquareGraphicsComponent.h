#pragma once
#include <array>
#include <SFML/Graphics.hpp>

#include "GraphicsComponent.h"

class SquareGraphicsComponent : public GraphicsComponent
{
public:
	SquareGraphicsComponent(sf::Shape* shape, std::array<sf::Vector2f, 4> worldCorners);
	virtual ~SquareGraphicsComponent();

	virtual void Update(const Entity& entity, sf::RenderWindow & window);

private:
	std::array<sf::Vector2f, 4> m_worldCorners;
};

