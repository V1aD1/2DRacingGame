#pragma once
//#include <SFML/Graphics.hpp>

#include "GraphicsComponent.h"

class CarGraphicsComponent : public GraphicsComponent
{
private:
	float circleRad = 2.0f;
	std::vector<sf::CircleShape> cornerCircles;

public:
	CarGraphicsComponent(sf::Shape* shape);
	virtual ~CarGraphicsComponent();

	virtual void Update(const Entity& entity, sf::RenderWindow & window) override;
};

