#pragma once
#include <array>
#include <SFML/Graphics.hpp>

#include "GraphicsComponent.h"

class SquareGraphicsComponent : public GraphicsComponent
{
private:
	float circleRad = 8.0f;
	std::vector<sf::CircleShape> cornerCircles;

public:
	SquareGraphicsComponent(sf::Shape* shape);
	virtual ~SquareGraphicsComponent();
	virtual void Update(const Entity& entity, sf::RenderWindow & window) override;
};

