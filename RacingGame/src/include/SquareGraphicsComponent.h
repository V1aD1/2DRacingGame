#pragma once
#include <array>
#include <SFML/Graphics.hpp>

#include "GraphicsComponent.h"

class SquareGraphicsComponent : public GraphicsComponent
{
private:
	float circleRad = 8.0f;
	std::vector<sf::CircleShape> cornerCircles;

private:
	void DBG_DrawCorners(const Entity& entity, sf::RenderWindow& window);

public:
	SquareGraphicsComponent(sf::Shape* shape);
	virtual ~SquareGraphicsComponent();
	virtual void Update(const Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
	virtual void HandleCollision(sf::Vector2f otherEntityMomentum) override;
};

