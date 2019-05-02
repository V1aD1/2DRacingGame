#pragma once

#include "GraphicsComponent.h"

class CarGraphicsComponent : public GraphicsComponent
{
private:
	float circleRad = 2.0f;
	std::vector<sf::CircleShape> cornerCircles;

private:
	void DBG_DrawCorners(const Entity& entity, sf::RenderWindow& window);

public:
	CarGraphicsComponent(sf::Shape* shape);
	virtual ~CarGraphicsComponent();

	virtual void Update(const Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
	virtual void HandleCollision(sf::Vector2f otherEntityMomentum) override;
};

