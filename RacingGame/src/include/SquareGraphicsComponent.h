#pragma once
#include <array>
#include <SFML/Graphics.hpp>

#include "GraphicsComponent.h"

class SquareGraphicsComponent : public GraphicsComponent
{
public:
	SquareGraphicsComponent(sf::Shape* shape);
	virtual ~SquareGraphicsComponent();
	virtual void Update(const Entity& entity, sf::RenderWindow & window);
};

