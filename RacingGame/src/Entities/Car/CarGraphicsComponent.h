#pragma once

#include "../../Components/GraphicsComponent.h"

class CarGraphicsComponent : public GraphicsComponent
{
private:
	float circleRad = 2.0f;
	std::vector<sf::CircleShape> cornerCircles;

private:
	void DBG_DrawCorners(const Entity& entity, sf::RenderWindow& window);

public:
	CarGraphicsComponent(sf::Shape* shape);
	~CarGraphicsComponent();

	void Update(const Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
};

