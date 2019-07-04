#pragma once
#include "GraphicsComponent.h"

class ShapeGraphicsComponent : public GraphicsComponent
{
private:
	float circleRad = 2.0f;
	std::vector<sf::CircleShape> cornerCircles;

private:
	void DBG_DrawCorners(const Entity& entity, sf::RenderWindow& window);

public:
	ShapeGraphicsComponent(sf::Shape* shape);
	~ShapeGraphicsComponent();

	void Update(Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
};

